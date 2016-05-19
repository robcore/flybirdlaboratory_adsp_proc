#ifndef MOTION_FEATURE_H
#define MOTION_FEATURE_H

/*=============================================================================
 Qualcomm Motion Feature header file

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
 * 2013-04-08  jayarama   changes for CMC 1.0
 * 2013-03-06  ks         initial version
 *
 *============================================================================*/
/**----------------------------------------------------------------------------
 * Include Files
 * --------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "fft.h"

#ifdef OFFTARGET_UNIT_TESTING
#define SNS_OS_MEMZERO( ptr, size) memset((ptr), 0, (size))
#define FX_FIXTOFLT_Q16(x) ((float)(x) / (float)(65536.0f))
#define FX_FLTTOFIX_Q16(x) ((int32_t) (x*65536))
#else
#include "sns_memmgr.h"
#include "sns_debug_str.h"
#include <fixed_point.h>
#endif

#define MOTION_FEATURE_ACCEL_COLS 3

/* Sample rate for accel stream in Hz*/
#define MOTION_FEATURE_SAMPLE_RATE (20)

#define MOTION_FEATURE_MAX 2

#define MOTION_FEATURE_MAX_SAMPLE_COUNT ((uint16_t)(-1))
/*maximum samples over which features can be computed. samples beyond this limit
 are fed, they are ignored in the feature computation*/

#define MOTION_FEATURE_ERR -1

/* Features used by GMM:
 * IQR, ModRM, MM3, DiffSum, Diff10P
 */
#define MOTION_FEATURE_GMM_NUM (5)

/* Features used by LR:
 * SA, SADiff, LinearAccel, LinearAccelDiff
 */
#define MOTION_FEATURE_LR_NUM (4)

/*
 * 10 one-sec-window for the sliding window and 1 one-sec-window for
 * temp storage of incoming accel
 */
#define MOTION_FEATURE_ONE_SEC_WINDOW_POOL_SIZE (11)

/* Size of the sliding window consisting of the one_sec_window
 *
 */
#define MOTION_FEATURE_MULTI_SEC_SLIDING_WINDOW_SIZE (10)

#define MOTION_FEATURE_TEN_PERCENT_OF_SLD_WINDOW (MOTION_FEATURE_MULTI_SEC_SLIDING_WINDOW_SIZE*MOTION_FEATURE_SAMPLE_RATE/10)

/*
 * Number of FFT points
 */
#define  FFT_NUM_POINTS        256

#define  FFT_LOG2_NUM_POINTS   8

typedef enum
{
   MOTION_FEATURE_IQR = 0,
   MOTION_FEATURE_MODRM = 1,
   MOTION_FEATURE_MM3 = 2,
   MOTION_FEATURE_DIFFSUM = 3,
   MOTION_FEATURE_DIFF10P = 4,
   MOTION_FEATURE_SA = 5,
   MOTION_FEATURE_SA_DIFF = 6,
   MOTION_FEATURE_LINEAR_ACCEL = 7,
   MOTION_FEATURE_LINEAR_ACCEL_DIFF = 8,
   MOTION_FEATURE_NUM = 9
} motion_feature_e;

// Used to index into the accel_norm_2_axis
typedef enum
{
   MOTION_FEATURE_X_Y_AXIS = 0,
   MOTION_FEATURE_X_Z_AXIS = 1,
   MOTION_FEATURE_Y_Z_AXIS = 2,
} motion_feature_2_axis_index_enum;

// Used to index into the FFT-based features.
// There is one FFT-based feature per component
typedef enum
{
   MOTION_FEATURE_A_COMP = 0,
   MOTION_FEATURE_AG_COMP = 1,
   MOTION_FEATURE_ANG_COMP = 2,
   MOTION_FEATURE_MAX_COMP = 3
} motion_feature_fft_comp_index_enum;
/*
 * Contains accel samples of 1 sec
 * and all temporary storage for computation of features
 * over the window
 */
typedef struct
{
   // Accel samples of the window. 0th accel is the earliest sample.
   struct
   {
      float axis[MOTION_FEATURE_ACCEL_COLS];
   } accel[MOTION_FEATURE_SAMPLE_RATE];

   int cnt; // Current count of number of accel samples

   struct
   {
      float axis[MOTION_FEATURE_ACCEL_COLS];
   } linear_accel[MOTION_FEATURE_SAMPLE_RATE];

   float accel_norm[MOTION_FEATURE_SAMPLE_RATE];


   // Norm computed from the Accel values of the X and Y axis, X and Z axis, Y and Z axis.
   float accel_norm_2_axis[MOTION_FEATURE_SAMPLE_RATE][3];

   float accel_sum[MOTION_FEATURE_ACCEL_COLS];
   float accel_norm_sum;

   // Norm Sum computed from the Accel values of the X and Y axis, X and Z axis, Y and Z axis.
   float accel_norm_2_axis_sum[3];

   struct
   {
      float axis[MOTION_FEATURE_ACCEL_COLS];
   } linear_accel_diff[MOTION_FEATURE_SAMPLE_RATE];

   float linear_accel_sum[MOTION_FEATURE_ACCEL_COLS];
   float linear_accel_diff_sum[MOTION_FEATURE_ACCEL_COLS];
   float sorted_accel_diff_norm[MOTION_FEATURE_SAMPLE_RATE];
   float accel_diff_norm_sum;
   float feature_iqr;
   float feature_modrm;
   float feature_mm3;

} motion_feature_one_sec_window;

/*
 * Pool of one_sec_window.
 * one_sec_window are allocated and released to this pool
 */
typedef struct
{
   motion_feature_one_sec_window win_list[MOTION_FEATURE_ONE_SEC_WINDOW_POOL_SIZE]; // List of one_sec_window
   bool allocated[MOTION_FEATURE_ONE_SEC_WINDOW_POOL_SIZE]; // Whether the corresponding one_sec_window is allocated or free
} motion_feature_one_sec_window_pool;

/* Sliding window of several one_sec_window
 */
typedef struct
{
   struct
   {
      motion_feature_one_sec_window* one_sec_win_ref; // Reference to the actual one_sec_window
      motion_feature_one_sec_window* next_one_sec_win_ref; // Pointer to one_sec_window next to this win in time
   } win_list[MOTION_FEATURE_MULTI_SEC_SLIDING_WINDOW_SIZE];

   // Number of windows in the sliding window. At startup, it is zero.
   // It will increment as windows are added, and then it maxes out at MOTION_FEATURE_MULTI_SEC_SLIDING_WINDOW_SIZE
   int cnt;

   uint32_t current_pos; // Position of first/latest window in the sliding window

   // Pool to which one_sec_windows that fall off the end of the sliding window need to be released.
   motion_feature_one_sec_window_pool* one_sec_win_pool;

   // Axis index (X=0, Y=1, Z=2) of gravity component "ag"
   uint8_t ag_axis_index;

   // Axis indices of non-gravity component "ang"
   uint8_t ang_axis_index[2];

   // Current absolute values of FFT results for A, AG and ANG
   float fft_abs_A[FFT_NUM_POINTS];
   float fft_abs_AG[FFT_NUM_POINTS];
   float fft_abs_ANG[FFT_NUM_POINTS];

   // Total spectral energy for A, AG and ANG
   float total_spectral_energy[MOTION_FEATURE_MAX_COMP];

   float feature_diffsum;
   float feature_diff10p;
   float feature_sa;
   float feature_sadiff;
   float feature_linear_accel[MOTION_FEATURE_ACCEL_COLS];
   float feature_linear_accel_diff[MOTION_FEATURE_ACCEL_COLS];
   float feature_se_0_2[MOTION_FEATURE_MAX_COMP];
   float feature_se_2_4[MOTION_FEATURE_MAX_COMP];
   float feature_se_5_10[MOTION_FEATURE_MAX_COMP];
   float feature_high_peak_mag[MOTION_FEATURE_MAX_COMP];
   float feature_high_peak_loc[MOTION_FEATURE_MAX_COMP];
   float feature_spec_ent[MOTION_FEATURE_MAX_COMP];
   float feature_mean_cross[MOTION_FEATURE_MAX_COMP];
} motion_feature_multi_sec_sliding_window;

typedef struct
{
   float accel[MOTION_FEATURE_ACCEL_COLS]; // accel, m/s/s
} motion_feature_input_s;

typedef struct
{
   float val;
} motion_feature_iqr_output_s;

typedef struct
{
   float val;
} motion_feature_modrm_output_s;

typedef struct
{
   float val;
} motion_feature_mm3_output_s;

typedef struct
{
   float val;
} motion_feature_diffsum_output_s;

typedef struct
{
   float val;
} motion_feature_diff10p_output_s;

typedef struct
{
   float val;
} motion_feature_sa_output_s;

typedef struct
{
   float val;
} motion_feature_sadiff_output_s;

typedef struct
{
   float val[3];
} motion_feature_linearaccel_output_s;

typedef struct
{
   float val[3];
} motion_feature_linearacceldiff_output_s;

typedef struct
{
   float val[3];
} motion_feature_se_0_2_output_s;

typedef struct
{
   float val[3];
} motion_feature_se_2_4_output_s;

typedef struct
{
   float val[3];
} motion_feature_se_5_10_output_s;

typedef struct
{
   float val[3];
} motion_feature_high_peak_mag_output_s;

typedef struct
{
   float val[3];
} motion_feature_high_peak_loc_output_s;

typedef struct
{
   float val[3];
} motion_feature_spec_ent_output_s;

typedef struct
{
   float val[3];
} motion_feature_mean_cross_output_s;

typedef struct
{
   bool features_ready;
   motion_feature_iqr_output_s iqr;
   motion_feature_modrm_output_s modrm;
   motion_feature_mm3_output_s mm3;
   motion_feature_diffsum_output_s diffsum;
   motion_feature_diff10p_output_s diff10p;
   motion_feature_sa_output_s sa;
   motion_feature_sadiff_output_s sadiff;
   motion_feature_linearaccel_output_s linear_accel;
   motion_feature_linearacceldiff_output_s linear_accel_diff;
   motion_feature_se_0_2_output_s se_0_2;
   motion_feature_se_2_4_output_s se_2_4;
   motion_feature_se_5_10_output_s se_5_10;
   motion_feature_high_peak_mag_output_s high_peak_mag;
   motion_feature_high_peak_loc_output_s high_peak_loc;
   motion_feature_spec_ent_output_s spec_ent;
   motion_feature_mean_cross_output_s mean_cross;
} motion_feature_output_s;

/* CMC algorithm state structure */
typedef struct
{
   motion_feature_e feature_id[MOTION_FEATURE_NUM];
   motion_feature_input_s input;
   motion_feature_output_s output;

   motion_feature_one_sec_window_pool one_sec_window_pool;

   motion_feature_multi_sec_sliding_window sld_win;

   // One-sec window currently being filled with accel
   motion_feature_one_sec_window* curr_one_sec_win;

   float filtered_accel[MOTION_FEATURE_ACCEL_COLS];
} motion_feature_state_s;

/**----------------------------------------------------------------------------
 * Function Prototypes
 * --------------------------------------------------------------------------*/

/*
 * Initialize motion feature module
 */
void motion_feature_init(motion_feature_state_s *state);

/*!
 Run feature computation.
 */
void motion_feature_update(motion_feature_state_s *state);

void motion_feature_one_sec_window_pool_init(motion_feature_one_sec_window_pool* pool);
motion_feature_one_sec_window* motion_feature_one_sec_window_pool_allocate(motion_feature_one_sec_window_pool* pool);
void motion_feature_one_sec_window_pool_release(motion_feature_one_sec_window_pool* pool, motion_feature_one_sec_window* win);

void motion_feature_multi_sec_sliding_window_init(motion_feature_multi_sec_sliding_window* sld_win, motion_feature_one_sec_window_pool* one_sec_win_pool);
void motion_feature_multi_sec_sliding_window_push_new_win(motion_feature_multi_sec_sliding_window* sld_win, motion_feature_one_sec_window* new_win);
uint32_t motion_feature_multi_sec_sliding_window_is_full(motion_feature_multi_sec_sliding_window* sld_win);

/* Returns the ith window in the sliding window. 0th is the latest window. */
motion_feature_one_sec_window* motion_feature_multi_sec_sliding_window_get_win(motion_feature_multi_sec_sliding_window* sld_win, uint32_t index);
motion_feature_one_sec_window* motion_feature_multi_sec_sliding_window_get_last_win(motion_feature_multi_sec_sliding_window* sld_win);
motion_feature_one_sec_window* motion_feature_multi_sec_sliding_window_get_prev_win(motion_feature_multi_sec_sliding_window* sld_win, uint32_t index);

void motion_feature_one_sec_window_init(motion_feature_one_sec_window* one_sec_win);
/*
 * Add new accel data to the one-sec-window.
 * Returns true if accel buffer inside window is full
 */
bool motion_feature_one_sec_window_add_accel(motion_feature_one_sec_window* one_sec_win, float x, float y, float z);

/* Certain computations that span window boundaries ( like accel diffs)
 * need to be done when a window knows its next neighbor
 */

void motion_feature_one_sec_window_compute_features(motion_feature_one_sec_window* one_sec_win, float filtered_accel[MOTION_FEATURE_ACCEL_COLS]);
void motion_feature_one_sec_window_set_next_ngbr(motion_feature_one_sec_window* one_sec_win, motion_feature_one_sec_window* next_ngbr);

void motion_feature_multi_sec_sliding_window_compute_features(motion_feature_multi_sec_sliding_window* one_sec_win);

void motion_feature_update_filtered_accel(float filtered_accel[MOTION_FEATURE_ACCEL_COLS], float accel[MOTION_FEATURE_ACCEL_COLS]);

void motion_feature_get_lowest_n(float* sorted_lists[MOTION_FEATURE_MULTI_SEC_SLIDING_WINDOW_SIZE], float lowest_n[MOTION_FEATURE_TEN_PERCENT_OF_SLD_WINDOW] );

#endif // MOTION_FEATURE_H
