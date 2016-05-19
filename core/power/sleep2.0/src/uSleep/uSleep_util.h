#ifndef USLEEP_UTIL_H
#define USLEEP_UTIL_H
/*==============================================================================
  FILE:         uSleep_util.h

  OVERVIEW:     Types & prototypes for internal utility uSleep functions

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/uSleep_util.h#2 $
$DateTime: 2014/11/06 11:48:29 $
==============================================================================*/
#include "DALStdDef.h"
#include "sleepi.h"
#include "uSleepi.h"

/*==============================================================================
                            DEFINITIONS & TYPES
 =============================================================================*/
/* String definitions for the resources required to turn DDR on/off */
#define USLEEP_NPA_RESOURCE_SNOC  "/clk/snoc"
#define USLEEP_NPA_RESOURCE_BIMC  "/clk/bimc"

/** 
 * uSleep_RPM_set_mode
 * 
 * @brief Enum to indicate which RPM data set(s) to send and how to wait for the
 *        response
 */
typedef enum uSleep_RPM_set_mode_s
{
  UIMAGE_ENTER  = 0,  /* Sends DDR off and does not wait */
  UIMAGE_EXIT,        /* Sends DDR on and blocks until ack is received. The
                         blocking may be parallelized so it is differentiated 
                         from exit_fast */ 
  UIMAGE_EXIT_FAST    /* Sends DDR on and blocks until ack is received */ 
}uSleep_RPM_set_mode;

/** 
 * uSleep_transition_profiling
 * 
 * @brief Data structure for tracking the mode transition times
 */
typedef struct uSleep_transition_profiling_s
{
  /* Timestamp of last uSleep entry point */
  uint64 entry_start_time;

  /* Timestamp of last uSleep exit point */
  uint64 exit_start_time;

  /* Current value of the time to enter uSleep */
  uint32 entry_latency;

  /* Current value of the time to exit uSleep */
  uint32 exit_latency;

  /* Statistics for transition times */
  sleepStats_generic  entry_stats;
  sleepStats_generic  exit_stats;

  /* Total entries into island mode */
  uint32 total_entries;

  /* Adjustement match value */
  uint32 adjust_count;
}uSleep_transition_profiling;

/** 
 * uSleep_global_data
 * 
 * @brief Global uSleep data structure that holds various states and data
 */
typedef struct uSleep_global_data_s
{
  /* Current internal uSleep state */ 
  uSleep_internal_state state;

  /* XO shutdown mode specific to uSleep mode */
  uSleep_CXO_mode XO_mode;

  /* DDR wakeup timer deadline */
  uint64 ddr_wakeup_timer; 

  /* Time of the last wakeup in uImage */
  uint64 last_wakeup_timestamp;

  /* Time of the last PMI interrupt in uImage */
  uint64 last_pmi_timestamp;

  /* Transition profiling data structure */
  uSleep_transition_profiling transition_data;
}uSleep_global_data;

/*==============================================================================
                          DDR FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleep_createQueryHandles
 * 
 * @brief Creates the various handles required to turn on and off DDR
 * 
 * @note This function must be called before the first entry into island mode
 *       while still in normal operational mode.
 */
void uSleep_createQueryHandles(void);

/**
 * uSleep_setDDRWakeupTimeInternal
 * 
 * @brief Sets the first non-deferrable timer from DDR so uSleep can compare 
 *        and use it if it is the next sytem wide timer to expire.
 *  
 * @param wakeupTimer:  Absolute time (in ticks) of the next non-deferrable 
 *                      normal operational timer. 
 */
void uSleep_setDDRWakeupTimeInternal(uint64 wakeupTimer);

/**
 * uSleep_setupIslandEntry
 * 
 * @brief Performs the final stages of island entry immediatly before island 
 *        mode is actually entered.        
 *  
 * @param BIMCFreq: Pointer given to retreive the current BMIC frequency which 
 *                  be used later to exit island mode.
 *  
 * @param SNOCFreq: Pointer given to retreive the current SNOC frequency which 
 *                  be used later to exit island mode.  
 */
void uSleep_setupIslandEntry(uint32 *BIMCFreq, uint32 *SNOCFreq);

/**
 * uSleep_completeTransitionToDDR
 * 
 * @brief Completes the island mode exit process.
 */
void uSleep_completeTransitionToDDR(void);

/*==============================================================================
                        ISLAND FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleep_islandControl
 * 
 * @brief Enters or exits island mode
 * 
 * @param flag: Enum to perform entry or exit transition actions
 */
void uSleep_islandControl(uSleep_RPM_set_mode flag);

/**
 * uSleep_setStateInternal
 * 
 * @brief Sets the current uSleep internal state
 * 
 * @param state: uSleep internal state to set
 */
void SLEEP_INLINE uSleep_setStateInternal(uSleep_internal_state state);

/**
 * uSleep_getStateInternal
 * 
 * @brief Gets the current uSleep internal state
 */
uSleep_internal_state SLEEP_INLINE uSleep_getStateInternal(void);

/**
 * uSleep_getDDRWakeupTimeInternal
 * 
 * @brief Gets the currently set DDR wakeup time as given to uSleep during 
 *        the entry transition.
 */
uint64 SLEEP_INLINE uSleep_getDDRWakeupTimeInternal(void);

/**
 * uSleep_setLastSleepWakeupInternal
 * 
 * @brief Sets the time of the wakeup from the last power cycle. 
 *  
 * @param wakeupTime: Absolute time of the last wakeup 
 */
void SLEEP_INLINE uSleep_setLastSleepWakeupInternal(uint64 wakeupTime);

/**
 * uSleep_getLastSleepWakeupInternal
 * 
 * @brief Gets the time of the wakeup from the last power cycle. 
 *  
 * @return Absolute time of the last wakeup. 
 */
uint64 SLEEP_INLINE uSleep_getLastSleepWakeupInternal(void);

/**
 * uSleep_getLastPMITimestampInternal
 * 
 * @brief Gets the time of the last PMI that occured while in uImage. 
 *  
 * @return Absolute time of the last PMI occurrence. 
 */
uint64 SLEEP_INLINE uSleep_getLastPMITimestampInternal(void);

/**
 * uSleep_setLastPMITimestampInternal
 * 
 * @brief Sets the time of the last PMI that occured while in uImage. 
 *  
 * @param PMITime: Absolute time of the last PMI occurrence. 
 */
void SLEEP_INLINE uSleep_setLastPMITimestampInternal(uint64 PMITime);

/**
 * uSleep_setCXOModeInternal
 * 
 * @brief Indicates if the master is allowed to vote for XO shutdown while in 
 *        uSleep.
 *  
 * @note This is not an aggregation as in normal operational mode.  The last 
 *       function call will set the current mode.
 *  
 * @param mode: Enable or disable XO voting from the master 
 */
void uSleep_setCXOModeInternal(uSleep_CXO_mode mode);

/**
 * uSleep_getCXOModeInternal
 * 
 * @brief Gets the currently set XO shutdown setting. 
 *  
 * @return Returns current CXO mode. 
 */
uSleep_CXO_mode SLEEP_INLINE uSleep_getCXOModeInternal(void);

/**
 * uSleep_getProfilingDataPtr
 * 
 * @brief Gets a pointer to the uSleep profiling data structure which can be 
 *        used to access data directly 
 */
uSleep_transition_profiling* uSleep_getProfilingDataPtr(void);

/** 
 * uSleep_transitionToNormalOperation
 * 
 * @brief Completes the tranistion to normal operational mode once DDR has been 
 *        turned on while in island mode.
 */
void uSleep_transitionToNormalOperation(void);

#endif /* USLEEP_UTIL_H */

