#ifndef USLEEPI_H
#define USLEEPI_H
/*==============================================================================
  FILE:         uSleepi.h

  OVERVIEW:     Internal interface functions and types for uSleep

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/uSleepi.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "uTimetick.h"
#include "uSleep.h"
#include "utimer.h"
#include "qurt.h"
#include "npa.h"

/*==============================================================================
                              INTERNAL VARIABLES
 =============================================================================*/
extern qurt_signal_t     g_uSleepExitSignal;

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/

/**
 * uSleep_idle_entry_ptr_type
 *
 * @brief Function pointer type for different behaviors when processor goes
 *        idle during uSleep interaction.
 */
typedef uint32 (*uSleep_idle_entry_ptr_type)(void);

/**
 * uSleep_internal_state
 * 
 * @brief Internal states for uSleep mode used to control tranistions and other
 *        behavior
 */
typedef enum uSleep_internal_state
{
  /* Steady mode state */
  uSLEEP_INTERNAL_STATE_IN_DDR          = 0x0001, 
  uSLEEP_INTERNAL_STATE_ACTIVE          = 0x0002,

  /* Entry transitions */
  uSLEEP_INTERNAL_STATE_FAST_ENTRY      = 0x0010, /* Not currently supported */
  uSLEEP_INTERNAL_STATE_FULL_ENTRY      = 0x0020,

  /* Exit transitions */
  uSLEEP_INTERNAL_STATE_REQ_FAST_EXIT   = 0x0100, /* Error fatal exit request */ 
  uSLEEP_INTERNAL_STATE_REQ_FULL_EXIT   = 0x0200, /* Normal exit complete request */
  uSLEEP_INTERNAL_STATE_REQ_TRANS_EXIT  = 0x0400, /* Normal exit stage 1 request
                                                     Used as holding stage while
                                                     RPM turns on DDR */

  /* Exited states */
  uSLEEP_INTERNAL_STATE_FAST_EXIT       = 0x1000,
  uSLEEP_INTERNAL_STATE_FULL_EXIT       = 0x2000,

  uSLEEP_INTERNAL_STATE_MAX
}uSleep_internal_state;

/**
 * uSleep_signals
 * 
 * @brief Signals to use to indicate callback function execution state between 
 *        different PD's
 */
typedef struct uSleep_signals_s
{
  qurt_anysignal_t start; /* Signal to start executing callbacks -user wait */ 
  qurt_signal_t    done;  /* Signal to indicate callbacks are done -guest wait*/
}uSleep_signals;

/**
 * uSleep_callback_list
 * 
 * @brief Main callback strucutre for guest PD
 */
typedef struct uSleep_callback_list_s
{
  uSleep_notification_cb_type   callbackFcn;
  struct uSleep_callback_list_s *next;
}uSleep_callback_list;

/**
 * uSleep_user_signal_cb_type
 * 
 * @brief User callback function prototype
 */
typedef uint32 (*uSleep_user_signal_cb_type)(uSleep_state_notification  state, 
                                             uSleep_signals             *signals);

/**
 * uSleep_user_callback_list
 * 
 * @brief Main callback strucutre for user PD which includes signals that guest
 *        PD will wait on when calling the user callbacks
 */
typedef struct uSleep_user_callback_list_s
{
  uSleep_user_signal_cb_type          callbackFcn;
  uSleep_signals                      *signals;
  struct uSleep_user_callback_list_s  *next;
}uSleep_user_callback_list;

/**
 * uSleep_callback_data
 * 
 * @brief Main callback structure that contains the two callback function lists
 *        as well as the total entry/exit latencies for the registered callbacks
 */
typedef struct uSleep_callback_data_s
{
  uint32                    enterLat;
  uint32                    exitLat;
  uSleep_callback_list      *functionList;
  uSleep_user_callback_list *userFunctionList;
}uSleep_callback_data;

/* Signal values to trigger the execution of user callbacks */
#define USLEEP_SIGNAL_START_ENTER     0x01
#define USLEEP_SIGNAL_START_EXIT      0x02 /* exit callbacks not currently called */

/* Signal value for guest PD to wait on for user callbacks to finished exeuction */ 
#define USLEEP_SIGNAL_DONE_FINISHED   0x01

/* Inital time (in ticks) required to enter uSleep */
#define USLEEP_SEED_ENTER_TIME   7000

/* Initial time (in ticks) required to exit uSleep.  This includes the DDR on
 * transition and worst case exit path time */
#define USLEEP_SEED_EXIT_TIME    (38500 + 5000)

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * uSleep_initialize
 * 
 * @brief Initialize the uSleep subsystem        
 */
void uSleep_initialize(void);

/**
 * uSleep_setIdleFunctionPtr
 *
 * @brief This function sets the idle entry point used by uSleep during next
 *        idle cycle.
 *
 * @param newIdleEntryPtr: Pointer to the function that will be called when
 *                         system is idle next time.
 */
void uSleep_setIdleFunctionPtr(uSleep_idle_entry_ptr_type newIdleEntryPtr);

/**
 * uSleep_getIdleFunctionPtr
 *
 * @brief Returns pointer to the idle entry point used by uSleep in next
 *        idle cycle.
 *
 * @return see @brief
 */
uSleep_idle_entry_ptr_type uSleep_getIdleFunctionPtr(void);

/** 
 * uSleep_entry
 * 
 * @brief Entry function to uSleep called from STM context. 
 *        uSleep entry is now committed.
 *  
 * @note Assumes function is called from STM via main sleep function 
 *  
 * @param DDRWakepTime: First non-deferrable timer from the normal operational
 *                      timer list.
 */
void uSleep_entry(uint64 DDRWakeupTime);

/** 
 * uSleep_worker
 * 
 * @brief Main uSleep function in island mode that will enter low power modes.
 */
uint32 uSleep_worker(void);

/** 
 * uSleepNode_initialize
 * 
 * @brief Initializes /core/uSleep node
 */
void uSleepNode_initialize(void);

/** 
 * uSleep_transitionNotify
 * 
 * @brief Notifies registered clients of a normal operational <-> island 
 *        transition.
 *  
 * @param state:  Enum of entry or exit transition 
 */
void uSleep_transitionNotify(uSleep_state_notification state);

/**
 * uSleep_setTransitionTime
 * 
 * @brief Sets the time it takes to transition in or out of uSleep
 *  
 * @param entryTicks: Time in ticks of entry transition
 * @param exitTicks:  Time in ticks of exit transition
 */
void uSleep_setTransitionTime(uint32 entryTicks, 
                              uint32 exitTicks);

/**
 * uSleep_getTransitionTime
 * 
 * @brief Returns the current value of the uSleep latency required to enter 
 *        and exit the mode 
 */
uint32 uSleep_getTransitionTime(void);

/** 
 * uSleep_guestClientInit
 * 
 * @brief Initializes the guest PD client data
 */
void uSleep_guestClientInit(void);

/** 
 * uSleep_workerExit
 * 
 * @brief Handles exiting LPR modes 
 */
void uSleep_workerExit(void);

/** 
 * uSleep_updateTransitionTimes 
 *  
 * @brief If necessary, will update the transition latency values to enter and 
 *        exit uSleep.
 *  
 * @note This must be called in normal operational mode. 
 */ 
void uSleep_updateTransitionTimes(void);

#endif /* USLEEPI_H */

