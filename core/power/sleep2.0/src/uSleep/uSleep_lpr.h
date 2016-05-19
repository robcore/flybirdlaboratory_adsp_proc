#ifndef USLEEP_LPR_H
#define USLEEP_LPR_H
/*==============================================================================
  FILE:         uSleep_lpr.h

  OVERVIEW:     Types & definitions for uSleep supported low power modes

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/uSleep_lpr.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                             INTERNAL DEFINITIONS
 =============================================================================*/
/* Index values into the modes in g_uSleepLPR */
typedef enum
{
  usleep_lpr_null_idx     = 0,
  usleep_lpr_cached_idx   = 1,
  usleep_lpr_apcr_idx     = 2,
  usleep_lpr_cxo_idx      = 3,

  usleep_lpr_last_idx     = 4
}usleep_lpr_index;

/* Number of LPR's supported in uSleep */
#define USLEEP_NUMBER_LOW_POWER_MODES   usleep_lpr_last_idx

/*==============================================================================
                               TYPE DEFINITIONS
 =============================================================================*/
/* LPR function types */
typedef void (*uSleep_LPR_enter_func)(uint64 wakeupTime);
typedef void (*uSleep_LPR_exit_func)(void);
typedef void (*uSleep_LPR_init_func)(boolean islandEntry);

/* LPR type for uSleep */
typedef struct usleep_LPR_s
{
  uint32                threshold;  /* Minimum sleep duration required */
  char                  *name;      /* Name of LPRM */
  uint32                latency;    /* Enter + exit latency in ticks of LPRM */
  uint32                backoff;    /* Backoff latency in ticks of LPRM */
  uSleep_LPR_init_func  init_func;  /* Setup function that is called on transition */
  uSleep_LPR_enter_func enter_func; /* Functions to call for LPRM */
  uSleep_LPR_exit_func  exit_func;
  boolean               cached;     /* Flag to indicate if mode is cacheable */
}uSleep_LPR;

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleepLPR_apcrEnter
 * 
 * @brief Enter function for un-cached APCR low power mode.
 * 
 * @param wakeupTime: Absolute wakeup time
 */
void uSleepLPR_apcrEnter(uint64 wakeupTime);

/**
 * uSleepLPR_apcrCachedEnter
 * 
 * @brief Enter function for cached APCR low power mode.
 * 
 * @param wakeupTime: Absolute wakeup time
 */
void uSleepLPR_apcrCachedEnter(uint64 wakeupTime);

/**
 * uSleepLPR_apcrExit
 * 
 * @brief Exit function for un-cached APCR low power mode
 */
void uSleepLPR_apcrExit(void);

/**
 * uSleepLPR_apcrCachedExit
 * 
 * @brief Exit function for cached APCR low power mode
 */
void uSleepLPR_apcrCachedExit(void);

/**
 * uSleepLPR_apcrInit
 * 
 * @brief This function is called while in normal operational mode and will 
 *        setup any requirements to enter APCR mode while in uSleep.
 *  
 * @param islandEntry: Flag to indicate if island mode is entering or exiting 
 */
void uSleepLPR_apcrInit(boolean islandEntry);

/**
 * uSleepLPR_cxoEnter
 * 
 * @brief XO shutdown LPR entry function
 * 
 * @param wakeupTime: Absolute wakeup time
 */
void uSleepLPR_cxoEnter(uint64 wakeupTime);

/**
 * uSleepLPR_cxoExit
 * 
 * @brief XO shutdown LPR exit function
 */
void uSleepLPR_cxoExit(void);

/**
 * uSleepLPR_cxoInit
 * 
 * @brief This function is called while in normal operational mode and will 
 *        setup any requirements to enter XO shutdown mode while in uSleep.
 *  
 * @param islandEntry: Flag to indicate if island mode is entering or exiting  
 */
void uSleepLPR_cxoInit(boolean islandEntry);

/**
 * uSleepLPR_init
 * 
 * @brief This function is called while in normal operational mode and executes 
 *        each low power mode's init function on the transition into island
 *        mode.
 *  
 * @param islandEntry: Flag to indicate if island mode is entering or exiting   
 */
void uSleepLPR_init(boolean islandEntry);

/** 
 * uSleepLPR_PMIPerformer
 * 
 * @brief Island mode version of the PMI interrupt handler routine.  
 */
void uSleepLPR_PMIPerformer(void);

/** 
 * uSleepLPR_setActiveMode
 * 
 * @brief Set the active low power mode that will be executed the next time 
 *        the system goes idle
 *  
 * @param index: Enum of the desired low power mode 
 */
void uSleepLPR_setActiveMode(usleep_lpr_index index);

/** 
 * uSleepLPR_runLPRFunctions
 * 
 * @brief Runs the currently selected low power mode enter or exit function 
 *  
 * @param enterFunction: TRUE   -> Run the currently selected LPRM enter 
 *                                 function
 *                       FALSE  -> Run the currently selected LPRM exit function
 *  
 * @param wakeupDeadline: Value (in absolute ticks) of the backoff adjusted 
 *                        desired wakeup time. 
 *                        If exit function is selected, this value is a don't
 *                        care.
 */
void uSleepLPR_runLPRFunctions(boolean enterFunction,
                               uint64  wakeupDeadline);

/** 
 * uSleepLPR_idleSolver
 * 
 * @brief Internally sets and returns the un-cacheable mode that should be 
 *        entered with the allowed amount of sleep time.  Once called, only
 *        uSleepLPR_runLPRFunctions(...) is required to enter the chosen mode.
 *   
 * @param wakeupDeadline: Value (in absolute ticks) of the hard deadline wakeup 
 *                        time.
 *  
 * @return Low power mode that should be entered
 */
uSleep_LPR *uSleepLPR_idleSolver(uint64 wakeupDeadline);

#endif /* USLEEP_LPR_H */

