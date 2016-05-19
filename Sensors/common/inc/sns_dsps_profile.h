/*============================================================================

  @file sns_dsps_profile.h

  @brief

            Copyright (c) 2011 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

============================================================================*/

/*============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/common/inc/sns_dsps_profile.h#1 $


when         who     what, where, why
----------   ---     ---------------------------------------------------------
2011-02-28   br      Changed pf_cpu_util_s structure and created pf_task_sw_s structure
2011-02-24   br      Initial Release

============================================================================*/

/*============================================================================

                                INCLUDE FILES

============================================================================*/
struct pf_msg_log_s;
#define PF_CPU_UTIL_MAX_CNT       (0x100)
#define PF_TASK_SW_MAX_CNT        (0x100)
#define PF_MSG_LOG_MAX_CNT        (0x2c000/sizeof(pf_per_msg_log_s))
#define PF_STK_CNT                0x03
#define PF_PER_MSG_LOG_SIZE       0x38
#define PF_CPU_UTIL_START_MSG_LOG_CNT 0x01
void App_TaskSwHook(void);
void sns_dsps_pf_int_hook(void);
void sns_dsps_pf_stat_task_init(void);
void sns_dsps_pf_smr_hook (sns_smr_header_s *msg_hdr_ptr);
void App_TimeTickHook (void);

typedef enum {
  PF_OFF = 0,
  PF_ON,
  PF_ALL_RESET
} pf_state_e;

typedef struct pf_config_s
{
  pf_state_e      state;          /* config state */
  void *          cpu_util_ptr;   /* pointer to the cpu utilization */
  void *          task_sw_ptr;    /* pointer to the task context switch infor */          
  void *          stk_log_ptr;    /* pointer to the stack profile ptr */
  void *          msg_log_ptr;    /* pointer to the msg log */
} pf_config_s;

typedef struct pf_cpu_util_s
{
  uint32_t        valid_cnt;      /* initialized to be 0 */
  uint32_t        idle_max_cnt;
  uint32_t        reserved[2];
  uint32_t        idle_run_cnt[PF_CPU_UTIL_MAX_CNT];
} pf_cpu_util_s;

typedef struct pf_per_task_sw_s
{
  uint32_t        ts;
  uint32_t        task_prio;
} pf_per_task_sw_s;

typedef struct pf_task_sw_s
{
  uint32_t          valid_cnt;      /* initialized to be 0 */
  uint32_t          reserved[3];
  pf_per_task_sw_s  per_task_sw[PF_TASK_SW_MAX_CNT];
} pf_task_sw_s;

typedef struct pf_stk_s
{
  uint8_t         eye_catcher[8]; /* eye catcher for the task Id such as "SAM", "SMGR", or "SMR" */
  uint32_t        free_wm;        /* the free space */
  uint32_t        high_wm;        /* the high watermark */
} pf_stk_s;

typedef struct pf_per_msg_log_s 
{
  uint32_t        ts;                   /* time stamp of the event manager */
  uint32_t        ext_ts;               /* extended time stamp: Optional  */
  uint32_t        ext_ts2;              /* extended time stamp 2: Optional */
  uint32_t        rsvd;
  uint8_t         msg[PF_PER_MSG_LOG_SIZE]; /* message body from SMR header */
} pf_per_msg_log_s;

typedef struct pf_msg_log_s 
{
  uint32_t          idx;                      /* cur index to write the log */
  uint32_t          reserved[3];              /* reserved for alignment*/
  pf_per_msg_log_s  msgs[PF_MSG_LOG_MAX_CNT]; /* array for message logging */
} pf_msg_log_s;

typedef struct sns_dsps_profile_s
{
  pf_config_s     config;
  pf_cpu_util_s   cpu_util;
  pf_task_sw_s    task_sw;
  pf_stk_s        stack[PF_STK_CNT];
  pf_msg_log_s    msg_log;
} sns_dsps_profile_s;
