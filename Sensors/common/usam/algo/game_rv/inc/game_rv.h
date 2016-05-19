#ifndef GAME_ROTATION_VECTOR_H
#define GAME_ROTATION_VECTOR_H

/*=============================================================================
  Qualcomm Game Rotation Vector header file

  Copyright (c) 2013-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
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
 * 2014-07-10  tc   Refactored for uSAM
 * 2013-05-06  tc   initial version
 *
 *============================================================================*/

#include <stdint.h>
#include <stdbool.h>
#include "fixed_point.h"
#include "sns_sam_algo_api.h"
#include "sns_sam_gravity_vector_v01.h"
#include "sns_sam_game_rotation_vector_v01.h"

#define GAME_ROT_VEC_NUM_QUAT_ELEMS (4)
#define GAME_ROT_VEC_GRAVITY_ELEMS  (3)
#define GAME_ROT_VEC_AZIMUTH_ELEMS  (3)
#define GAME_ROT_VEC_NUM_ELEMS      (4)

//#define USE_SINGLE_PRECISION_FLOAT

#ifdef USE_SINGLE_PRECISION_FLOAT
typedef float game_rv_float;
#else
typedef double game_rv_float;
#endif

typedef enum
{
   GAME_ROT_VEC_GRAVITY_DATA,
   GAME_ROT_VEC_GYRO_QUAT_DATA
} game_rot_vec_input_e;

typedef enum
{
   GAME_ROT_VEC_ANDROID_COORD_SYS,  // Android (ENU = East North Up)
   GAME_ROT_VEC_SAE_COORD_SYS       // SAE (NED = North East Down)
} game_rot_vec_coord_sys_e;

typedef struct
{
   uint8_t accuracy;
   float gravity[GAME_ROT_VEC_GRAVITY_ELEMS];
   sns_sam_gravity_dev_e_v01 device_state;
} game_rot_vec_gravity_t;

typedef struct
{
   float quaternion[GAME_ROT_VEC_NUM_QUAT_ELEMS];
} game_rot_vec_gyro_quat_t;

typedef struct
{
   game_rv_float azimuth[GAME_ROT_VEC_AZIMUTH_ELEMS];
} game_rot_vec_gyro_azimuth_t;

typedef struct
{
   game_rv_float w;
   game_rv_float x;
   game_rv_float y;
   game_rv_float z;
} game_rot_vec_quat_t;

/* Game Rotation Vector configuration structure */
typedef struct
{
   q16_t sample_rate;         // sample rate in Hz, Q16
   q16_t min_report_rate;     // minimum report rate requested for dependent sensors
   game_rot_vec_coord_sys_e coordinate_sys; // coordinate system, 0 = Android, 1 = SAE
} game_rot_vec_config_s;

/* Game Rotation Vector input structure */
typedef struct
{
   union
   {
      game_rot_vec_gravity_t gravity;
      game_rot_vec_gyro_quat_t gyro_quat;
   } data;
   game_rot_vec_input_e input_type;
} game_rot_vec_input_s;

/* Game Rotation Vector output structure */
typedef struct
{
   uint8_t accuracy;
   game_rot_vec_coord_sys_e coordinate_sys; // coordinate system, 0 = Android, 1 = SAE
   float rotation_vector[GAME_ROT_VEC_NUM_QUAT_ELEMS];
   sns_sam_timestamp timestamp;
} game_rot_vec_output_s;

/* Game Rotation Vector state structure */
typedef struct
{
   game_rot_vec_config_s  config;
   game_rot_vec_gravity_t gravity_vector;
   sns_sam_timestamp grav_timestamp;
   game_rot_vec_gyro_quat_t gyro_quaternion;
   sns_sam_timestamp quat_timestamp;
   game_rot_vec_gyro_azimuth_t  gyro_azimuth;

   /* Calculated Game Rotation Vector */
   float rotation_vector[GAME_ROT_VEC_NUM_ELEMS];
   sns_sam_timestamp timestamp;
   float abs_rest_gyro_azimuth_tilt_alpha;
   float rel_rest_gyro_azimuth_tilt_alpha;
   float motion_gyro_azimuth_tilt_alpha;
   /* Gyro-quaternion noise floor adjusted for update rate */
   float gyro_noise_threshold;
   float max_gyro_azimuth_tilt_freeze_limit;
   float max_gyro_azimuth_tilt_reset_limit;
   uint32_t min_in_rest_count;
   uint32_t in_abs_rest_count;
   uint32_t in_rel_rest_count;
   /* effective report rate requested for dependent sensor*/
   q16_t report_rate;
} game_rot_vec_state_s;

/* Game Rotation Vector persistent data */
typedef struct {
  /* If the registry data for Game Rotation Vector has been received*/
  bool reg_data;
  /* Consumption for the gyro sensor as reported by SMGR */
  uint64_t power_grav;
  /* Maximum sampling rate*/
  q16_t max_sample_rate;
  /* Maximum sampling rate*/
  q16_t min_sample_rate;
  /* Default configuration values */
  game_rot_vec_config_s def_config;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *grav_suid;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *quat_suid;
} game_rot_vec_persist_s;

#endif
