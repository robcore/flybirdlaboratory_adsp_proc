#ifndef SLEEP_IDLE_PLUGIN_H
#define SLEEP_IDLE_PLUGIN_H
/*============================================================================
  FILE:         sleep_idle_plugin.h

  OVERVIEW:     This file provides the externs and declarations needed for the
                sleep idle plugin subsystem.
 
  DEPENDENCIES: None

                Copyright (c) 2011-2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
==============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/npa_nodes/sleep_idle_plugin.h#1 $
$DateTime: 2014/10/16 12:45:40 $
============================================================================*/
#include "npa.h"

/*==============================================================================
                            GLOBAL DEFINITIONS
 =============================================================================*/
/**
 * SLEEP_IDLE_PLUGIN_CLIENT_LPM_HOLD_OFF
 *
 * @brief NPA client type that can hold off Sleep from executing any
 *        low power modes.
 */
#define SLEEP_IDLE_PLUGIN_CLIENT_LPM_HOLD_OFF         NPA_CLIENT_CUSTOM1

/**
 * SLEEP_IDLE_PLUGIN_CLIENT_ALLOW_USLEEP
 *
 * @brief NPA client type to indicate it's ok to enter uSleep mode
 */
#define SLEEP_IDLE_PLUGIN_CLIENT_ALLOW_USLEEP         NPA_CLIENT_CUSTOM2

/*==============================================================================
                           FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * sleepIdlePlugin_initialize
 * 
 * @brief Initialize the sleep idle plugin subsystem.  This function registers 
 *        the idle plugin node. 
 */
void sleepIdlePlugin_initialize( void );

#endif /* SLEEP_IDLE_PLUGIN_H */

