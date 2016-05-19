#ifndef USLEEP_H
#define USLEEP_H
/*==============================================================================
  FILE:         uSleep.h

  OVERVIEW:     Provides the API interface functions and types for uSleep

  DEPENDENCIES: Functions prototyped here are located in the island code section
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/api/power/sleep2.0/uSleep.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                              DEFINES & TYPES
 =============================================================================*/
/* uSleep API function error codes */
#define USLEEP_SUCCESS  0
#define USLEEP_FAILURE  1

/**
 * uSleep_CXO_mode
 *
 * @brief Enumeration for the sleep modes available in uSleep mode
 */
typedef enum uSleep_CXO_mode
{
  USLEEP_CXO_SHUTDOWN_ENABLE    = 0, /* Enable CXO shutdown in uSleep */
  USLEEP_CXO_SHUTDOWN_DISABLE   = 1, /* Disable CXO shutdown in uSleep */
  USLEEP_CXO_SHUTDOWN_MAX_MODE  = 2  /* Maximum value */ 
}uSleep_CXO_mode;

/**
 * uSleep_state_notification
 *
 * @brief Enumeration for the uSleep notification callbacks
 */
typedef enum uSleep_state_notification
{
  USLEEP_STATE_ENTER = 0,  /* uSleep mode is about to be entered */
  USLEEP_STATE_EXIT        /* uSleep mode has been exited */
}uSleep_state_notification;

/**
 * uSleep_notification_cb_handle
 *
 * @brief Handle to registered callback notification function
 */
typedef uint32 uSleep_notification_cb_handle; 

/**
 * uSleep_notification_cb_type
 *
 * @brief Callback notification function prototype
 */
typedef void (*uSleep_notification_cb_type)(uSleep_state_notification state);

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/** 
 * uSleep_exit
 * 
 * @brief Explicitly exit uSleep mode.
 *        Will enable DDR and exit uImage mode at the next idle period
 * 
 * @note This function only exits uSleep mode, it will not disable it and
 *       uSleep could be entered again on the next sleep cycle.
 *       It is only intended to be called while in uImage mode.
 * 
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
uint32 uSleep_exit(void);

/** 
 * uSleep_exitOnError
 * 
 * @brief Explicitly exit uSleep mode without calling function callbacks
 *        Will enable DDR and exit immediately.
 * 
 * @note This function is intended to only be called from the OS in a 
 *       FATAL ERROR case. It does not allow reentry into any type of sleep
 *       modes and will loop forever if system is allowed to enter the idle
 *       state again.
 *       It is only intended to be called while in uImage mode.
 */
void uSleep_exitOnError(void);

/** 
 * uSleep_notifyDDRTransitionComplete
 * 
 * @brief Notifies uSleep that the DDR transtion has been completed.
 *        
 * @note This function is intended to only be called from the RPM driver to 
 *       indicate that a DDR transaction is complete.
 *  
 * @param ddrOn: TRUE   -> DDR has been turned on 
 *               FALSE  -> DDR has been turned off
 */
void uSleep_notifyDDRTransitionComplete(uint8 ddrOn);

/** 
 * uSleep_setCXOMode
 * 
 * @brief Explicitly set whether to vote for XO shutdown or not. 
 *  
 * @note This function is only intended to be called while in uImage mode 
 * 
 * @param mode: ENUM xo enabled/disabled 
 *  
 * @return USLEEP_SUCCESS or USLEEP_FAILURE
 */
uint32 uSleep_setCXOMode(uSleep_CXO_mode mode);

/** 
 * uSleep_registerNotificationCallback
 * 
 * @brief Registers a client callback function for notification when uSleep 
 *        is entered or exited 
 *  
 * @note  This function must be called during initialization while in DDR 
 *        mode.
 *  
 *        The registered function will be called while in single threaded
 *        mode and must not invoke other threads or otherwise exit STM.
 * 
 *        The registered function should be as minial as possible to keep the
 *        transtion times as fast as possible. 
 *     
 *  
 * @param enterLat: Time in ticks taken to execute the CB when entering uImage
 * @param exitLat:  Time in ticks taken to execute the CB when exiting uImage
 * @param callback: Function to be called
 *  
 * @return Handle of registered function; 0 = error
 */
uSleep_notification_cb_handle uSleep_registerNotificationCallback(
                                uint32                      enterLat,
                                uint32                      exitLat,
                                uSleep_notification_cb_type callback);

#endif /* USLEEP_H */

