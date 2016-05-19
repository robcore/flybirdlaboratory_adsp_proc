#ifndef CLIENT_GUEST_H
#define CLIENT_GUEST_H
/*==============================================================================
  FILE:         client_guest.h

  OVERVIEW:     uSleep guest client types

  DEPENDENCIES: None
  
                Copyright (c) 2014 Qualcomm Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Technologies Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/power/sleep2.0/src/uSleep/client_guest/client_guest.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"

/*==============================================================================
                            FUNCTION DECLARATIONS
 =============================================================================*/
/**
 * uSleep_registerUserNotificationCallback
 * 
 * @brief Function that is called once during user PD callback registration
 *        that will add a guest callback to signal the user callbacks to
 *        execute
 * 
 * @param signals: Handshake signals used to coordinate the guest-user callback
 *                 system. These signals are specific to each seperate user PD.
 * 
 * @return USLEEP_SUCCESS or USLEEP_FAILURE 
 */
uint32 uSleep_registerUserNotificationCallback(uSleep_signals *signals);

/**
 * uSleep_addUserCallbackLatency 
 *  
 * @brief Helper function that adds the enter/exit latencies for a callback 
 *        function
 *  
 * @note  This function should not be called directly, it will be called 
 *        appropriately via the registration API
 * 
 * @param enterLat: Enter latency (in ticks) of the callback being registered 
 * @param exitLat:  Exit latency (in ticks) of the callback being registered 
 *  
 * @return USLEEP_SUCCESS or USLEEP_FAILURE 
 */
uint32 uSleep_addUserCallbackLatency(uint32 enterLat, uint32 exitLat);

#endif /* CLIENT_GUEST_H */

