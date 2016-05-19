/*============================================================================

  @file sns_freerun_timer.h

  @brief
    This API implements for a free-run-timer

            Copyright (c) 2010 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

============================================================================*/

/*============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/common/inc/sns_freerun_timer.h#1 $


when         who     what, where, why
----------   ---     ---------------------------------------------------------
2010-10-05   br      Initial Release

============================================================================*/

/*============================================================================

                                INCLUDE FILES

============================================================================*/
#include "msmhwioreg.h"
#include "HALhwio.h"

#define PXO_24_576_MHZ (24576*1000)

/*!
  @brief This macro returns the tick of a free-run timer 
*/
#define SNS_FREE_RUN_TIMER_GET(timer_id) HWIO_INI(TCXO_TMRn_COUNT_VAL, timer_id)

/*===========================================================================

  FUNCTION:   sns_free_timer_enable

===========================================================================*/
/*!
  @brief This function enables the platform specific free-run timer
   
  @detail
  
  @param[i] timer_id to be enabled. The value can be either 0 or 1 for 9660 as an example.

  @return
   None
*/
/*=========================================================================*/
void sns_freerun_timer_enable ( uint32_t timer_id );

/*===========================================================================

  FUNCTION:   sns_free_timer_disable

===========================================================================*/
/*!
  @brief This function disables the platform specific free-run timer
   
  @detail
  
  @param[i] timer_id to be enabled. The value can be either 0 or 1 for 9660 as an example

  @return
   None

*/
/*=========================================================================*/
void sns_freerun_timer_disable ( uint32_t );

/*===========================================================================

  FUNCTION:   sns_freerun_timer_get_usec

===========================================================================*/
/*!
  @brief This function returns a gap between two ticks with usec value
   
  @detail
  
  @param[i] start_val the start tick value
  @param[i] now_val the now tick value

  @return
   None

*/
/*=========================================================================*/
uint32_t sns_freerun_timer_get_usec ( uint32_t timer_id, uint32_t start_val, uint32_t now_val );

/*===========================================================================

  FUNCTION:   sns_freerun_timer_get_hz

===========================================================================*/
/*!
  @brief This function returns the timer hz.
   
  @detail
  
  @param[i] timer_id the timer id on which this function returns the rate

  @return
   None

*/
/*=========================================================================*/
uint32_t sns_freerun_timer_get_hz ( uint32_t timer_id );
