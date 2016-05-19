#ifndef SNS_SMGR_MAIN_H
#define SNS_SMGR_MAIN_H
/*=============================================================================
  @file sns_smgr_main.h

  This header file contains the data definitions used within the DSPS
  Sensor Manager (SMGR)

******************************************************************************
* Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Confidential and Proprietary - Qualcomm Technologies, Inc.
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_main.h#4 $ */
/* $DateTime: 2015/05/22 16:04:29 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-04-21  pn   Removed deprecated field new_sample_idx
  2015-03-10  jms  - Calculate unified FIFO WM from max report rate of sensors in this FIFO
                   - Removed unused/ineffective discrete FIFO synch code
  2014-12-05  pn   Added powerstate to sns_smgr_sensor_s
  2014-09-25  pn   Added bigImage depot
  2014-09-11  pn   Protects all shared sensor state variables, not just client DB
  2014-09-08  pn   Moved PM interface functions to PM_IF module
  2014-07-31  pn   Removed POWER_INTERFACE featurization
  2014-07-09  vy   Added support for non-refactored DD
  2014-06-26  pn   Removed obsolete HP ODR table
  2014-06-16  pn   Updated sns_smgr_client_stat_s
  2014-06-05  vy   Added function declarations   
  2014-05-28  tc   SubHz Sampling
  2014-05-24  vy   Added function declarations
  2014-05-12  tc   Converted frequencies to fixed point, Q16. This is to
                   accommodate frequencies less than 1. Q16 fixed point is
                   used, instead of floating point, because the Q6 does not
                   have hardware-support for floating point division.
  2014-05-15  MW   Make lpf_table q16
  2014-05-13  vy   Refactored for uImage and PM support
  2014-05-09  pn   Removed no longer used sensor range structure definitions
  2014-05-07  pn   Removed unused code
  2014-04-23  pn   Initial version

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_ddf_attrib.h"
#include "sns_ddf_driver_if.h"
#include "sns_em.h"
#include "sns_queue.h"
#include "sns_rh.h"
#include "sns_smgr.h"
#include "sns_smgr_depot.h"
#include "sns_smgr_fifo.h"
#include "sns_pm.h"

/*----------------------------------------------------------------------------
 * Constants
 * -------------------------------------------------------------------------*/
#define MAX_HP_ODR_TB_SIZE                3

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/*
 * SMGR time sturcture for scheduling
*/
typedef struct smgr_tick32s_s
{
  uint32_t low_tick;
  uint32_t high_tick;
} smgr_tick32s_s;

typedef union    smgr_tick_s
{
  uint64_t tick64;
  smgr_tick32s_s u;
} smgr_tick_s;

/*----------------------------------------------------------------------------
 * Structure Definitions
 * -------------------------------------------------------------------------*/

/*  =============== Schedule structure ===============
    Contains scheduling parameters. One for each requested reporting
    rate, and one for each sensor for sensor-specific scheduling data.
    Report and sensor leader blocks point here for scheduling information.
    This structure is used for deconflicting reporting rates. Deconfliction
    happens when a new rate is introduced to the SOL mix or a rate becomes
    disused or we need to modify the maximum sampling rate.

    When a report is added or has its rate modified it needs to link to one
    of these structures, adding a new structure if introducing a new rate.
    Each active sensor needs a structure here, too. The structures must be
    added when the need is recognized, although they will not be initialized
    until later. If too few blocks are available, the new request must be
    rejected. Excess blocks will be returned when deconfliction happens.
*/
typedef struct  smgr_sched_block_s
{
  /* Chain schedule structures together in order: heartbeat then
     shortest to longest reporting/sampling intervals */
  sns_q_link_s                        sched_link;

  /* Maintain all sensor types belonging to this schedule block */
  sns_q_s                             ddf_sensor_queue;

  /* Requested rate */
  q16_t                               sampling_rate;

  /* The current scheduling interval by clock ticks. This tick is calculated by req_rate */
  uint32_t                            sched_intvl;

  /* Current assigned interval, scheduling clock ticks. Zero if not
     initialized */
  uint32_t                            next_tick;
} smgr_sched_block_s;

/* Only valid when smgr_sensor_state_e is SENSOR_STATE_READY */
typedef enum
{
  SENSORTYPE_STATE_IDLE,
  SENSORTYPE_STATE_READ_PENDING,
} smgr_sensor_type_state_e;

typedef struct
{
  sns_q_s                       request_queue;
  sns_smgr_ddf_sensor_s*        ddf_sensor_ptr; /* associated DDF sensor */
  uint32_t                      last_status_ts; /* ts of the most recent event */
} sns_smgr_sensor_status_s;

typedef struct
{
  /* when one or more of these fields change the report rate must be recomputed */
  sns_ddf_odr_t   odr;
  q16_t           depot_data_rate;
  q16_t           max_req_sampling_rate;
  sns_ddf_time_t  last_updated;
} sns_smgr_client_modifier_s;

typedef struct
{
  sns_smgr_sensor_status_s  sensor_status;

  /* singly-linked list of report items */
  sns_rh_rpt_item_s*        rpt_item_ptr;
  uint8_t                   num_rpt_items;
  uint8_t                   num_periodic_reports;
  uint8_t                   flags;

  /* highest requested rate amongst all high performance requests */
  q16_t                     max_high_perf_freq_hz;

  /* highest requested rate amongst all reports */
  q16_t                     max_requested_freq_hz;
  sns_smgr_client_modifier_s  client_modifier;

} sns_smgr_client_stat_s;

struct sns_smgr_ddf_sensor_s
{
  /* link to sampling schedule queue */
  sns_q_link_s                sched_link;

  /* the sensor to which this DDF sensor belongs */
  sns_smgr_sensor_s*          sensor_ptr;
  uint8_t                     data_type;    /* primary or secondary */
  uint8_t                     flags;

  sns_smgr_ddf_sensor_info_s* ddf_sensor_info;

  sns_smgr_sample_depot_s*    uimg_depot_ptr;
  sns_smgr_sample_depot_s*    bimg_depot_ptr;
  OS_EVENT*                   depot_mutex_ptr;
  bool                        bimg_depot_in_use;
  bool                        uimg_depot_full_alert;
  uint16_t                    num_new_samples;

  sns_smgr_client_stat_s      client_stat;

  /* calibration data */
  sns_smgr_all_cal_s*         all_cal_ptr;

  smgr_sensor_type_state_e    sensor_type_state;
  uint32_t                    data_poll_ts; /* timestamp when data was last polled */

  /* the ODR configured in device */
  sns_ddf_odr_t               current_odr;
  uint32_t                    current_wakeup_rate_hz;

  /* ratio between current ODR and max requested rate;
     only one in device_sampling_factor samples will go into the depot */
  // todo: consider changing this to a 32-bit integer, to prevent possible overflows
  uint8_t                     device_sampling_factor;

  /* the sampling frequency of data in depot; 
     = device_sampling_rate/device_sampling_factor 
     only greater than 1 when HP clients exist and no CIC request */
  q16_t                       depot_data_rate;
  uint32_t                    depot_data_interval;

  /* highest supported rate; provided by DD at init */
  q16_t                       max_supported_freq_hz;

  /* count down from dri_ratio to 0 */
  uint8_t                     dri_count;

  /* keeps track of number of skipped samples */
  uint8_t                     max_skipped_samples;

};

/*  =============== SensorLeader structure ===============
    Contains VARIABLE parameters to manage collection from a sensor
*/
struct sns_smgr_sensor_s 
{
  /* references the static table entry for the sensor */
  const smgr_sensor_cfg_s*        const_ptr;

  /* handle to driver object */
  sns_ddf_handle_t                dd_handle;
  
  /* Registry item parameters for device driver initialization */
  sns_ddf_nv_params_s             reg_item_param;

  /* Define sensors available from this device. The driver populates this
     at initialization */
  uint8_t                         num_data_types;
  sns_smgr_ddf_sensor_s*          ddf_sensor_ptr[SMGR_MAX_DATA_TYPES_PER_DEVICE];

  sns_smgr_protected_q_s          request_queue;

  /* Use memhandler for each device in short read. Minimize time delay between
     reading one sensor and the next */
  sns_ddf_memhandler_s            memhandler;

  /* Number of Low Pass Filters in hardware */
  uint8_t                         num_lpf;
  q16_t                           lpf_table[SMGR_MAX_LPF_FREQ_IN_SENSOR];

  /* ODRs supported by DD */
  sns_ddf_odr_t*                  supported_odrs;
  uint8_t                         num_odrs;

  /* Initialization state */
  sns_smgr_sensor_init_state_e    init_state;

  /* Sensor state (actually applies to a device driver) */
  sns_smgr_sensor_state_e         sensor_state;
  sns_ddf_powerstate_e            powerstate;

  /* Flags to coordinate reading registry */
  uint8_t                         flags;

  uint32_t                        event_done_tick;
  uint32_t                        odr_change_tick; /* timestamp at last ODR config */

  OS_EVENT*                       mutex_ptr;

  /* Sensor FIFO Configuration */
  smgr_sensor_fifo_cfg_s          fifo_cfg;

  //flag set to true/false when intr enabled/disabled in sns_smgr_enable_sched_data
  //initially set to false in sns_smgr_sensor_init
  bool                            is_self_sched_intr_enabled; //is intr enabled (is in DRI/self sched mode)?
  bool                            odr_attr_supported;
  
  /* refactored for uImage mode or not */
  bool                            is_uimg_refac;

};

typedef struct
{
  /* input */
  sns_smgr_single_sensor_test_req_msg_v01* self_test_req;
  sns_smgr_ddf_sensor_s*          ddf_sensor_ptr;

  /* output */
  sns_smgr_sensor_state_e         pre_test_state;
  sns_smgr_self_test_result_s     result;
} sns_smgr_self_test_s;

/*  =============== Smgr QMD structure ===============
    Contains QMD related info for SMGR
*/

typedef struct  
{
  /* State of overall device driver initialization */
  sns_smgr_sensor_all_init_state_e  all_init_state;
  uint32_t                          init_start_tick;
  sns_smgr_sensor_s                 sensor[SNS_SMGR_NUM_SENSORS_DEFINED];
  intptr_t                          uimg_depot_mem_ptr;
  intptr_t                          bimg_depot_mem_ptr;

  /* the tick value of current scheduling time */
  smgr_tick_s                  sched_tick;

  /* queue for schedule blocks */
  sns_q_s                      sched_que;

  /* flags used for multiple purposes */
  uint8_t                      flags;

  /* sns_smgr.last_tick is to maintain 64 bits timeticks per sns_smgr_get_tick64().
   * high_tick could be increased only if sns_smgr_get_tick64() was called. */
  smgr_tick_s                  last_tick;

  sns_em_timer_obj_t           tmr_obj;
  sns_em_timer_obj_t           sensor_ev_tmr_obj;

  bool                         md_is_enabled;
  bool                         app_is_awake;
  uint32_t                     app_state_toggle_count;

  OS_FLAG_GRP*                 sig_grp;
  OS_FLAGS                     sig_flag;

  void*                        timer_que[SNS_SMGR_TIMER_QUEUE_SIZE];
  uint8_t                      timer_que_in;
  uint8_t                      timer_que_out;

  /* SSI sensor dependent reg items state */
  uint16_t                     last_requested_sensor_dep_reg_group_id;
  uint16_t                     last_received_reg_group_id;
  
  sns_smgr_self_test_s         self_test;

} sns_smgr_s;

#define SNS_DRI_SIMULATE       0x1
typedef struct
{
  OS_STK                       DRITask[SNS_MODULE_STK_SIZE_DSPS_PLAYBACK];
  uint8_t                      dri_sim_task_created;
  uint8_t                      start_irq;
  OS_FLAG_GRP                  *sns_dri_sig_grp;
} sns_dri_sim_s;

extern smgr_sensor_cfg_s       smgr_sensor_cfg[SNS_SMGR_NUM_SENSORS_DEFINED ];
extern sns_smgr_s              sns_smgr;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

extern void sns_smgr_sensor_init(void);

extern void sns_smgr_sampling_cycle(void);

extern void sns_smgr_dd_init(void);

extern void sns_smgr_schedule_sensor_event(uint32_t tick_offset);

extern void smgr_process_sensor_event(void);

extern void sns_smgr_set_all_sensors_state(sns_smgr_sensor_state_e state);

extern void smgr_process_dri_fifo_async_data(
  sns_smgr_ddf_sensor_s*        ddf_sensor_ptr,
  const sns_ddf_sensor_data_s*  data_ptr);

extern void sns_smgr_update_sampling_setting(
  sns_smgr_ddf_sensor_s*  ddf_sensor_ptr);

extern void sns_smgr_update_odr(sns_smgr_ddf_sensor_s* ddf_sensor_ptr);

extern void sns_smgr_sensor_ev_timer_cb(void *cb_arg);

extern void sns_smgr_timer_cb(void *cb_arg);

extern void sns_smgr_task(void* p_arg);

extern void sns_smgr_task_main(void);

extern void sns_smgr_app_state_change(bool app_is_asleep);

extern void sns_smgr_handle_bigimage_signals(OS_FLAGS sig_flags);

#endif /* #ifndef SNS_SMGR_MAIN_H */

