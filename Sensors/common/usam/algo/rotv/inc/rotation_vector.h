#ifndef ROTATION_VECTOR_H
#define ROTATION_VECTOR_H

/*=============================================================================
  Qualcomm Rotation Vector header file

  Copyright (c) 2011, 2013-2015 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

/*===========================================================================
  Include Files
  ===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "fixed_point.h"
#include "sns_sam_algo_api.h"

/*============================================================================
  Preprocessor Definitions and Constants
  ===========================================================================*/
#define ROTATION_VECTOR_COL   (4)
#define GRAVITY_COL (3)
#define MAGNETIC_COL (3)

#define ROTATION_VECTOR_ANDROID_COORD_SYS 0 // Android (ENU = East North Up)
#define ROTATION_VECTOR_SAE_COORD_SYS 1     // SAE (NED = North East Down)

/*============================================================================
  Type Declarations
  ===========================================================================*/

typedef enum
{
  ROTV_COORD_SYS_ANDROID = 0,
  ROTV_COORD_SYS_SAE = 1,
} rotv_coord_sys;

typedef struct
{
  float gravity[GRAVITY_COL];
  uint8_t accuracy;
} gravity_vector_t;

typedef struct
{
  float filtered_mag[MAGNETIC_COL];
  uint8_t accuracy;
} magnetic_vector_t;

typedef struct
{
  /* Sample rate in Hz */
  q16_t sample_rate;
  /* minimum report rate requested for dependent sensors */
  q16_t min_report_rate;
  /* Coordinate system used in output, 0=SAE (default), 1=Android  */
  uint8_t coordinate_sys;
} rotation_vector_config_s;

typedef enum
{
  ROT_VEC_INPUT_GRAVITY = 0,
  ROT_VEC_INPUT_FMV = 1
}rotation_vector_input_type;

typedef struct
{
  rotation_vector_input_type input_type;
  union
  {
  gravity_vector_t gravity_vector;
  magnetic_vector_t mag_vector;
  }data;
} rotation_vector_input_s;

typedef struct
{
  float rotation_vector[ROTATION_VECTOR_COL];
  sns_sam_timestamp timestamp;
  uint8_t accuracy;
  rotv_coord_sys coordinate_sys;
} rotation_vector_output_s;

typedef struct
{
  rotation_vector_output_s last_output;
  rotation_vector_config_s config;
  gravity_vector_t gravity_vector;
  sns_sam_timestamp gravity_vector_ts;
  magnetic_vector_t mag_vector;
  sns_sam_timestamp mag_vector_ts;
  bool gravity_received;
  bool mag_vector_received;
  /*  effective report rate requested for dependent sensor*/
  q16_t report_rate;
} rotation_vector_state_s;

/* Rotation Vector persisitant data */
typedef struct {
  /* If the registry data for Rotation Vector has been received*/
  bool recv_reg_data;
  /* Consumption for the Gravity Vector algorithm as reported by SAM */
  uint64_t power_grav;
  /* Consumption for the FMV algorithm as reported by SAM */
  uint64_t power_fmv;
  /* Maximum sampling rate*/
  q16_t max_sample_rate;
  /* Minimum sampling rate*/
  q16_t min_sample_rate;
  /* Default configuration values */
  rotation_vector_config_s def_config;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *grav_suid;
  /* SUID saved in dep_sensors_met() */
  sns_sam_sensor_uid const *fmv_suid;
} rotation_vector_persist_s;

/*============================================================================
  Function Declarations
  ===========================================================================*/

/**
* Register the Rotation Vector algorithm
*
* See sns_sam_algo_register
*/
sns_sam_err rotv_sam_register(
      sns_sam_algo_api **algoAPI,
      sns_sam_algo_msg_api **msgAPI,
      qmi_idl_service_object_type *serviceObj,
      sns_sam_sensor_uid *sensorUID );

#endif