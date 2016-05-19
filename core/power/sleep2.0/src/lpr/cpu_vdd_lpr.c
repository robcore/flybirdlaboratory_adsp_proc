/*==============================================================================
  FILE:         cpu_vdd_lpr.c

  OVERVIEW:     This file provides the sleep LPR definition for the
                QDSP6V4 ALL WAIT low-power modes.

  DEPENDENCIES: None

                Copyright (c) 2010-2014 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/lpr/cpu_vdd_lpr.c#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "CoreTime.h"
#include "CoreVerify.h"
#include "DALStdDef.h"
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
#include "qurt.h"
#include "HALhwio.h"
#include "spm.h"
#include "adsppm.h"
#include "q6_lpm_config.h"

/*==============================================================================
                             GLOBAL VARIABLES
 =============================================================================*/
/**
 * @brief Handle for communicating with the clk driver to turn off PLL 
 *        before PC.
 */
static DalDeviceHandle *g_cpuClockHandle;

/**
 * @brief Time at which Sleep timer was programmed to wake up the master 
 *        during standalone low power modes.
 */
static uint64 g_expectedWakeupTick = 0;

/*==============================================================================
                      INTERNAL FUNCTIONS FOR CPU VDD LPR'S MODES
 =============================================================================*/

/** 
 * cpuVddLPR_Q6LPMEnter 
 *  
 * @brief Parameterized call to prepare core for different low power modes.
 * 
 * @param coreMode: Mode to which SPM HW will be programmed to 
 *                  execute appropriate command sequence.
 * @param L2Mode: Mode in which core's L2 cache will be kept.
 * @param wakeupTick: Absolute count of wakeup @19.2MHz
 */
static void cpuVddLPR_Q6LPMEnter
( 
  spm_low_power_mode_type coreMode,
  l2_lprm                 L2Mode,
  uint64                  wakeupTick 
)
{
  boolean isRPMAssistedMode;
  int32   qurt_shutdown_type = 0;

#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  uint64 tempTimeTick;
  uint64 enterLatency = CoreTimetick_Get64();
#endif

  /* Entering a Q6 LPM consists of two parts:
   * i) Configure Registers for LPM    
   * ii) Execute Software to trigger LPM      
   * 
   * If Q6 LPM is being entered at active time via cached mode
   * then only (i) is required. If Q6 is entering LPM via
   * uncached mode, both (i) and (ii) are required. */
  if( sleepOS_isProcessorInSTM() == FALSE )
  {
    q6LPMConfig_setupModeConfig( coreMode, FALSE );
    return ;
  }
  else
  {
    q6LPMConfig_setupModeConfig( coreMode, TRUE );
  }

  if(SPM_MODE_PWRC == coreMode)
  {
    if(L2Mode == L2_NORET)
    {
      qurt_shutdown_type = QURT_POWER_CMD_PERFORM;
    }
    else if(L2Mode == L2_RET)
    {
      qurt_shutdown_type = QURT_POWER_CMD_PERFORM_L2_RETENTION;
    }    
    else
    {
      CORE_VERIFY(NULL);
    }
  }

  isRPMAssistedMode = sleepTarget_getRPMAssistedMode();

  /* Program the wakeup timer only if not in a RPM assisted mode.
   * Value could be modified as part of call, so set to value returned */
  if (FALSE == isRPMAssistedMode)
  {
    g_expectedWakeupTick = sleepTarget_enableSleepTimer(wakeupTick);
  }

  /* Calling ADSPPM API to ramp down resources (e.g. AHB clock). This
   * request may or may not take effect depending on actual aggregation from 
   * ADSPPM clients */
  ADSPPM_EnterSleep();

  CORE_DAL_VERIFY(DalClock_ProcessorSleep(g_cpuClockHandle, 
                                          CLOCK_SLEEP_MODE_POWER_COLLAPSE,
                                          CLOCK_SLEEP_FLAG_RAMP_UP_CPU));

#ifdef SLEEP_ENABLE_AUTO_LPR_PROFILING
  /* Save power collapse type*/
  sleepStats_putMiscData(L2Mode , SLEEP_STATS_MISC_PC_L2_MODE_TYPE);
    
  tempTimeTick = CoreTimetick_Get64(); 
  sleepStats_putLprTimeData(tempTimeTick, 
                            SLEEP_STATS_TIME_MSTR_SHUTDOWN_TYPE);

  /* Calculate local enter latency time */
  enterLatency = tempTimeTick - enterLatency;
  sleepStats_putLprLatency((uint32)enterLatency, 
                           SLEEP_STATS_ENTER_LATENCY_TYPE);
#endif

  /* QURT functions perform all wait */ 
  if(SPM_MODE_PWRC == coreMode)
  {
    CORE_VERIFY(QURT_EOK == qurt_power_shutdown_enter(qurt_shutdown_type));
  }
  else if((coreMode == SPM_MODE_APCR_PLL_ON)  ||
          (coreMode == SPM_MODE_APCR_PLL_LPM))
  {
    CORE_VERIFY(QURT_EOK == qurt_power_apcr_enter());
  }
  else
  {
    CORE_LOG_VERIFY(0, sleepLog_printf(SLEEP_LOG_LEVEL_WARNING, 1,
                                       "Invalid coreMode: 0x%x",
                                       coreMode));
  }

  return;
}

/** 
 * cpuVddLPR_Q6LPMExit 
 *  
 * @brief Will be called when exiting from power collapse after sleep
 *
 * @param coreMode: Mode to which SPM HW was programed to 
 *                  execute command sequence while entering low
 *                  power mode.
 */
static void cpuVddLPR_Q6LPMExit ( spm_low_power_mode_type coreMode )
{
  boolean           isRPMAssistedMode;
  uint64            start_time;
  uint32            lprm_time;
  RPM_master_stats  *rpmStats       = sleepStats_getRpmDataPtr();
  static uint64     lastBringupAck  = 0;

  CORE_VERIFY_PTR(rpmStats);

  /* Check if we are in an RPM assisted mode */
  isRPMAssistedMode = sleepTarget_getRPMAssistedMode();

  /* Catch errors where RPM didn't update its statistics */
  if(TRUE == isRPMAssistedMode)
  {
    CORE_VERIFY(rpmStats->bringup_ack > lastBringupAck);
    lastBringupAck = rpmStats->bringup_ack;
  }

  /* Restore resources as necessary */
  CORE_DAL_VERIFY(DalClock_ProcessorRestore(g_cpuClockHandle,
                                            CLOCK_SLEEP_MODE_POWER_COLLAPSE,
                                            CLOCK_SLEEP_FLAG_RAMP_UP_CPU));
  
  ADSPPM_ExitSleep();

  sleepTarget_disableSleepTimer();

  /* Configure the Q6 for Clock Gating when exiting any LPRM */
  q6LPMConfig_setupModeConfig(SPM_MODE_CLK_GATE, FALSE);

  if(FALSE == isRPMAssistedMode)
  {
    sleepStats_wakeup_reason  reason;
    uint64                    master_wakeup_tick;

    /* Obtain time when control return to Sleep exit path */
    master_wakeup_tick = 
      sleepStats_getLprTimeData(SLEEP_STATS_TIME_MSTR_RETURN_TYPE);

    /* For standalone PC, wakeup time is scheduled QTimer value or earliest
     * possible point of return to Sleep module */
    if( master_wakeup_tick > g_expectedWakeupTick )
    {
      reason = SLEEP_STATS_WAKEUP_SA_SCHEDULED;

      /* use set Qtimer value as wakeup time */
      master_wakeup_tick = g_expectedWakeupTick;
    }
    else
    {
      reason = SLEEP_STATS_WAKEUP_SA_UNSCHEDULED;
    }

    /* Set stand alone PC wakeup reason and wakeup time in Stats */
    sleepStats_putMiscData(reason, SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);

    start_time = master_wakeup_tick;
  }
  else
  {
    /* In RPM assisted modes, the wakeup time will come from RPM. Get that here 
     * so it can be used to calculate proper cpu_vdd backoff latency. */
    start_time = inp64(&rpmStats->bringup_ack);

    /* Set wakeup reason as given from RPM */
    sleepStats_putMiscData(inpdw(&rpmStats->wakeup_reason), 
                           SLEEP_STATS_MISC_WAKEUP_REASON_TYPE);
  }

  /* Set master wakeup time */
  sleepStats_putLprTimeData(start_time, SLEEP_STATS_TIME_WAKEUP_TYPE);

  lprm_time = (uint32)(CoreTimetick_Get64() - start_time);
  sleepStats_putLprLatency(lprm_time, SLEEP_STATS_BACKOFF_LATENCY_TYPE);

  return;
}

/*==============================================================================
                              GLOBAL FUNCTIONS
 =============================================================================*/
/** 
 * cpuVddLPR_initialize
 *  
 * @brief Initialize cpu vdd LPR
 */
void cpuVddLPR_initialize(void)
{ 
  /* Attaching a handle for clock */
  CORE_DAL_VERIFY(DAL_ClockDeviceAttach(DALDEVICEID_CLOCK, 
                                        &g_cpuClockHandle));

  /* Common Q6SS register setup for all low power modes defined for
   * cpuVdd LPR. */
  q6LPMConfig_setupBase();

  /* Enabling SPM */
  spm_enable( 0, TRUE );

  /* Set up Clock Gate as default Mode */
  q6LPMConfig_setupModeConfig( SPM_MODE_CLK_GATE, FALSE );

  return;
}

/**
 * cpuVddLPR_pcNonRetentionEnter
 *
 * @brief This function will be called while entering into the power collapse 
 *        mode with l2 non retention (flushed).
 *
 * @param wakeupTick: Time at which master is expected to wake up.
 */
void cpuVddLPR_pcNonRetentionEnter(uint64 wakeupTick)
{
  cpuVddLPR_Q6LPMEnter(SPM_MODE_PWRC, L2_NORET, wakeupTick);
  return;
}

/** 
 * cpuVddLPR_pcExit 
 *  
 * @brief Exit function of power collapse low power mode.
 */
void cpuVddLPR_pcExit(void)
{
  cpuVddLPR_Q6LPMExit(SPM_MODE_PWRC);
  return;
}

/**
 * cpuVddLPR_pcRetentionEnter
 *
 * @brief This function will be called while entering into the power collapse 
 *        mode with l2 retention.
 *
 * @param wakeupTick: Time at which master is expected to wake up.
 */
void cpuVddLPR_pcRetentionEnter(uint64 wakeupTick)
{
  cpuVddLPR_Q6LPMEnter(SPM_MODE_PWRC, L2_RET, wakeupTick);
  return;
}

/** 
 * cpuVddLPR_APCR_RailOffEnter 
 *  
 * @brief Enter function for APCR with rail in low power mode.
 */
void cpuVddLPR_APCR_PLL_LPM_Enter( uint64 wakeupTick )
{
  cpuVddLPR_Q6LPMEnter(SPM_MODE_APCR_PLL_LPM, L2_RET, wakeupTick);
  return;
}

/** 
 * cpuVddLPR_APCR_RailOffExit 
 *  
 * @brief Exit function for APCR with rail in low power mode
 */
void cpuVddLPR_APCR_PLL_LPM_Exit( void )
{
  cpuVddLPR_Q6LPMExit( SPM_MODE_APCR_PLL_LPM );
  return;
}

/** 
 * cpuVddLPR_APCR_Enter 
 *  
 * @brief Enter function for APCR mode (Short Sequence in Q6HPG)
 */
void cpuVddLPR_APCR_Enter( uint64 wakeupTick )
{
  cpuVddLPR_Q6LPMEnter( SPM_MODE_APCR_PLL_ON, L2_RET, wakeupTick );
  return;
}

/** 
 * cpuVddLPR_APCR_Exit 
 *  
 * @brief Exit function for APCR mode (Short Sequence in Q6HPG)
 *
 * @note Can be moved NULL function once support is in Sleep framework
 */
void cpuVddLPR_APCR_Exit( void )
{
  q6LPMConfig_setupModeConfig( SPM_MODE_CLK_GATE, FALSE );
  return;
}

/**
 * cpuVddLPR_clkGateEnter
 *
 * @brief Enter function for clock gating low power mode
 */
void cpuVddLPR_clkGateEnter( uint64 wakeupTick )
{
  q6LPMConfig_setupModeConfig( SPM_MODE_CLK_GATE, FALSE );
  return;
}

/**
 * cpuVddLPR_clkGateExit
 *
 * @brief Exit function for clock gating low power mode
 *
 * @note Can be moved NULL function once support is in Sleep framework
 */
void cpuVddLPR_clkGateExit( void )
{
  return;
}

