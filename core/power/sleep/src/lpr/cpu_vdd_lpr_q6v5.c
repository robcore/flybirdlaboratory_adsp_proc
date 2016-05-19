/*==============================================================================
  FILE:         cpu_vdd_lpr.c

  OVERVIEW:     This file provides the sleep LPR definition for the
                QDSP6V4 ALL WAIT low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2010-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep/src/lpr/cpu_vdd_lpr_q6v5.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "CoreTime.h"
#include "CoreVerify.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALSys.h"
#include "DALSysTypes.h"
#include "DDIClock.h"
#include "sleep_lpr.h"
#include "sleepi.h"
#include "sleep_log.h"
#include "sleep_target.h"
#include "sleep_statsi.h"
#include "sleep_log.h"
#include "qurt.h"
#include "HALhwio.h"
#include "spm.h"
#include "Halsleep_hwio.h"
#include "adsppm.h"
#include "DALStdDef.h"
#include "DDIChipInfo.h"
#include "vmpm.h"

/*===========================================================================
 *                           MACRO DEFINITIONS
 *==========================================================================*/

/**
 * @brief SLEEP_L2NON_RET_OFFSET_FROM_MPM_BASE
 *
 * Macro to indicate offset of RPM L2 flag from VMPM base address in message 
 * RAM area.
 */
#define SLEEP_L2NON_RET_OFFSET_FROM_MPM_BASE (-4)

/*============================================================================
 *                            GLOBAL VARIABLES
 *============================================================================*/

/**
 * @brief cpu_clock_handle
 *
 * Handle for communicating with the clk driver to turn off PLL 
 * before PC.
 */
static DalDeviceHandle *cpu_clock_handle;

/**
 * @brief sleep_l2_nonret_pc
 *
 * Pointer to the flag in the message RAM area to indicate if Master is going
 * in to Power Collapse with L2 non retention.
 *
 * This flag will be set to 1 while entering L2 non retention based power 
 * collapse and will be cleared upon exit.
 *
 * NOTE: Used only on 8974 targets for now.
 */
static uint32 *sleep_l2_nonret_pc = NULL;

/**
 * @brief sleep_rpm_controlled_l2_non_ret
 *
 * Flag to indicate if L2 will be turned off by RPM during non retention based
 * power collapse. As of now only 8974 targets need this solution.
 */
static boolean sleep_rpm_controlled_l2_non_ret = FALSE;

/**
 * @brief sleep_l2nr_data_config_value
 *
 * Variable holding L2 data field value based on target code is running on. 
 * For targets where L2 is tunred off by RPM, it will be 0 otherwise it will
 * be 0x7 as recommended by HW team.
 */
static uint32 sleep_l2nr_data_config_value = 0x7;

/*=============================================================================
 *                             INTERNAL FUNCTIONS
 *=============================================================================*/
/**
 * @brief configure_spm_for_pc
 */
static void configure_spm_for_pc_enter(void)
{
  /* config EN_ARES/EN_CLAMP/EN_CLK according to HPG_QDSP6v5SS Rev.A */
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_ARES,  0x3F);
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_CLAMP, 0x1);
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_CLK,   0x3F);

  /* enable BHS */
  HWIO_OUT(LPASS_QDSP6SS_SPMCTL_EN_BHS,   0x01);  

  /* Program the SPM to do power collapse */
  spm_set_low_power_mode( 0, SPM_MODE_PWRC );

  /* Enabling the SPM */
  spm_enable( 0, TRUE );
}

/*===========================================================================
 *                             GLOBAL FUNCTIONS
 *==========================================================================*/

/**
 * @brief parameteried call to transition Q6 to PC modes
 * 
 * @param wakeup_tick: Absolute count of wakeup @19.2MHz
 * @param l2_mode    : @see l2_lprm definition
 */
static inline void sleep_q6_cfg_lpm( uint64 wakeup_tick, 
                                     l2_lprm l2_mode )
{
  sleepStats_wakeup_reason  reason;
  uint64                    tmp_time;
  boolean                   is_rpm_assisted;
  int                       im_timeout          = 200;
  int                       qurt_shutodwn_type  = 0;
  
#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  uint64 time_dt = CoreTimetick_Get64();
#endif

  is_rpm_assisted = sleep_target_get_rpm_assisted_mode();

  configure_spm_for_pc_enter();

  /* Prevent the L2VIC from sending interrupts to the QDSP6 Core */
  HWIO_OUT( LPASS_QDSP6SS_PD_HS_START, 1 );

  while (!(HWIO_IN(LPASS_QDSP6SS_PD_HS_DONE) & 
          HWIO_FMSK(LPASS_QDSP6SS_PD_HS_DONE, DONE))) 
  {
    im_timeout--;
   
    if(im_timeout == 0)
    { 
      ERR_FATAL( "Entering SW QDSP6 Power Collapse, IM Timeout.", 0, 0, 0 );
    }
  }

  switch (l2_mode)
  {
    case L2_NORET:
    {
      qurt_shutodwn_type = QURT_POWER_CMD_PERFORM;
      break;
    }

    case L2_RET:
    {
      qurt_shutodwn_type = QURT_POWER_CMD_PERFORM_L2_RETENTION;
      break;
    }

    default:
    {
      CORE_VERIFY(NULL);
    }
  }

  /* Program the wakeup timer only if not in a RPM assisted mode.
   * Value could be modified as part of call, so set to value returned */
  if (FALSE == is_rpm_assisted)
  {
    wakeup_tick = sleep_target_enable_sleep_timer(wakeup_tick);
  }

  /* Calling ADSPPM API to ramp down resources (e.g. AHB clock). This
   * request may or may not take affect depending on actual aggregation from 
   * ADSPPM clients */
  ADSPPM_EnterSleep();

  CORE_DAL_VERIFY(DalClock_ProcessorSleep(cpu_clock_handle, 
                                          CLOCK_SLEEP_MODE_POWER_COLLAPSE,
                                          CLOCK_SLEEP_FLAG_RAMP_UP_CPU));

#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  /* Save power collapse type*/
  sleepStats_putMiscData(l2_mode, SLEEP_STATS_MISC_PC_L2_MODE_TYPE);
    
  tmp_time = CoreTimetick_Get64(); 
  sleepStats_putLprTimeData(tmp_time, SLEEP_STATS_TIME_MSTR_SHUTDOWN_TYPE);

  /* Calculate local enter latency time */
  time_dt =  tmp_time - time_dt;
  sleepStats_putLprLatency((uint32)time_dt, SLEEP_STATS_ENTER_LATENCY_TYPE);
#endif

  /**** Do actual power collapse ****/
  qurt_power_shutdown_enter(qurt_shutodwn_type);

  CORE_DAL_VERIFY(DalClock_ProcessorRestore(cpu_clock_handle, 
                                            CLOCK_SLEEP_MODE_POWER_COLLAPSE,
                                            CLOCK_SLEEP_FLAG_RAMP_UP_CPU));

  /* First point of return after coming from Power Collapse - restore
   * resources which were ramped down */
  ADSPPM_ExitSleep();

  /* Record wakeup time as early as possible in master code - Need ADSPPM and 
   * clock to restore resources first otherwise steps may take longer time */
  tmp_time = CoreTimetick_Get64();

#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  sleepStats_putLprTimeData(tmp_time, SLEEP_STATS_TIME_MSTR_RETURN_TYPE);
#endif

  if (FALSE == is_rpm_assisted)
  {
    /* Set standalone wakeup reason based on current time and requested scheduled 
     * wakeup time */
    if (tmp_time > wakeup_tick)
    {
      reason    = SLEEP_STATS_WAKEUP_SA_SCHEDULED;
      tmp_time  = wakeup_tick;  /* use set qtmr value for real wakeup time */
    }
    else
    {
      reason = SLEEP_STATS_WAKEUP_SA_UNSCHEDULED;
    }

    /* Set stand alone PC wakeup reason */
    sleepStats_putMiscData(reason, SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);
  
    /* Set wakeup time as either the qtmr value, or the earliest possible point
     * in return to master code 
     * (RPM assisted will overwrite value in RPM assisted cases)*/
    sleepStats_putLprTimeData(tmp_time, SLEEP_STATS_TIME_WAKEUP_TYPE);
  }

  return;
}

/**
 * @brief cpu_vdd_lpr_init
 *
 * Initializes the CPUVDD LPR. This function basically gets a handle to FPGA
 * for easier debugging purpose.
 */
void cpu_vdd_lpr_init( void )
{ 
  DalChipInfoFamilyType chip_family;
  DalChipInfoVersionType chip_version;

  /* Attaching a handle for clock */
  CORE_VERIFY(DAL_ClockDeviceAttach(DALDEVICEID_CLOCK, &cpu_clock_handle)
              == DAL_SUCCESS);

  sleep_target_get_CPU_arch( &chip_family, &chip_version );

  /* Target specific initialization if any */
  if( DALCHIPINFO_FAMILY_MDM9x25 == chip_family )
  {
    /* Preparing registers to have support for enabling LDO */
    HWIO_OUTF( LPASS_QDSP6SS_SPMCTL_EN_LDO, VREF_SEL, 0x0 );
    HWIO_OUTF( LPASS_QDSP6SS_SPMCTL_EN_LDO, FORCEOFF, 0x7 );
    HWIO_OUTF( LPASS_QDSP6SS_SPMCTL_EN_LDO, FORCEON, 0x0 );
    HWIO_OUTF( LPASS_QDSP6SS_SPMCTL_EN_LDO, BYPASS_OPEN, 0x3 );    
  }
  /* Add code for any other target as required */
              
  return;   
}

/**
 * @brief cpu_vdd_pc_no_retention_enter
 *
 * This function will be called while entering into the power collapse mode.
 *
 * @param duration_sclk: The amount of time system will sleep for
 */
void cpu_vdd_pc_no_retention_enter( uint64 wakeup_tick )
{
  sleep_q6_cfg_lpm( wakeup_tick, L2_NORET );
}

/**
 * @brief cpu_vdd_pc_retention_enter
 *
 * This function will be called while entering into the power collapse mode.
 *
 * @param duration_sclk: The amount of time system will sleep for
 */
void cpu_vdd_pc_retention_enter( uint64 wakeup_tick )
{
  sleep_q6_cfg_lpm( wakeup_tick, L2_RET );
}

/**
 * @brief cpu_vdd_pc_exit
 *
 * Will be called when exiting from power collapse after sleep
 */
void cpu_vdd_pc_exit( void )
{
#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  uint64 start_time = CoreTimetick_Get64();
  uint32 lprm_time;
#endif

  sleep_target_disable_sleep_timer();
  
  spm_enable(0, FALSE);

#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  lprm_time = (uint32)(CoreTimetick_Get64() - start_time);
  sleepStats_putLprLatency(lprm_time, SLEEP_STATS_BACKOFF_LATENCY_TYPE);
#endif

  return;
}

/**
 * @brief l2_cache_init
 *
 * Initialization function for L2 cache LPR. It will set up certain target
 * specific data/values.
 */
void l2_cache_init( void )
{
  DalChipInfoFamilyType chip_family;
  DalChipInfoVersionType chip_version;

  /* Obtaining vMPM base address for this master */
  sleep_l2_nonret_pc = 
  (uint32 *)(vmpm_getProcMpmBaseVA() + SLEEP_L2NON_RET_OFFSET_FROM_MPM_BASE);

  sleep_target_get_CPU_arch( &chip_family, &chip_version );

  /* target specific setup */
  if( DALCHIPINFO_FAMILY_MSM8974 == chip_family ||
      DALCHIPINFO_FAMILY_MSM8974_PRO == chip_family )
  {
    /* L2 is turned off by RPM on this target */
    sleep_rpm_controlled_l2_non_ret = TRUE;
    sleep_l2nr_data_config_value = 0x0;
  }
  
}

/**
 * @brief l2_no_retention_enter
 *
 * Function that will be called while entering L2 non retention low power mode.
 */
void l2_no_retention_enter( uint64 wakeup_tick )
{
  /* 
   * HPG_QDSP6v5SS Rev.A Page 20:
   * MEM_PERIPH[19] set to 1
   * L2DATA_STBY[18] 0:off 1:on
   * L2source bias (on or off); only set with L2 retention.
   * Recommended to be cleared during initial silicon bring up until the
   * leakage saving feature is characterized in silicon
   * ETB retention (0:yes or 1:no)
   * L2TAG retention (0:yes or 1:no)
   * L2DATA[2:0] Each bit controls the L2 memory retention in 256kB
   * granularity (full 768kB L2 retention or none)
   */
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_MEM,
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, MEM_PERIPH, 0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA_STBY, 0x0 )|
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, ETB, 0x1 )        |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, L2TAG, 0x1 )      |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA, 
                       sleep_l2nr_data_config_value ) );

  if( TRUE == sleep_rpm_controlled_l2_non_ret )
  {
    /* RPM is turning off L2 on this target. Indicate to it about this mode */
    *sleep_l2_nonret_pc = 1;
  }
}

/**
 * @brief l2_no_retention_exit
 *
 * Function that will be called while exiting from L2 non retention mode.
 */
void l2_no_retention_exit( void )
{
  if( TRUE == sleep_rpm_controlled_l2_non_ret )
  {
    /* Clearing non retention flag */
    *sleep_l2_nonret_pc = 0;
  }  
}

/**
 * @brief l2_retention_enter
 *
 * Function that will be called while entering L2 retention low power mode.
 */
void l2_retention_enter( uint64 wakeup_tick )
{
  /* 
   * HPG_QDSP6v5SS Rev.A Page 20:
   * MEM_PERIPH[19] set tp 1
   * L2DATA_STBY[18] 0:off 1:on
   * L2source bias (on or off); only set with L2 retention.
   * Recommended to be cleared during initial silicon bring up until the
   * leakage saving feature is characterized in silicon
   * ETB retention (0:yes or 1:no)
   * L2TAG retention (0:yes or 1:no)
   * L2DATA[2:0] Each bit controls the L2 memory retention in 256kB
   * granularity (full 768kB L2 retention or none)
   */
  HWIO_OUT( LPASS_QDSP6SS_SPMCTL_EN_MEM,
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, MEM_PERIPH, 0x1 ) |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA_STBY, 0x1 )|
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, ETB, 0x0 )        |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, L2TAG, 0x0 )      |
            HWIO_FVAL( LPASS_QDSP6SS_SPMCTL_EN_MEM, L2DATA, 0x0 ) );
}

/**
 * @brief l2_retention_exit
 *
 * Function that will be called while exiting from L2 retention mode.
 */
void l2_retention_exit( void )
{
  /* Empty function */
}

