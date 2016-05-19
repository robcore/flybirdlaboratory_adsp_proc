#ifndef UCLOCK_H
#define UCLOCK_H
/*
===========================================================================
*/
/**
  @file ClockDefs.h
  @brief Public definitions include file for accessing the clock device driver.
*/
/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      This file is the public header file for the sensors micro image (uImage)
      clock driver implementation.  It is meant to be used by a small subset
      of drivers supporting the sensors uImage feature, which cannot access
      DDR.

===========================================================================*/
/*
  ===========================================================================

  Copyright (c) 2013 QUALCOMM Technologies Incorporated.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/api/systemdrivers/uClock.h#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  12/17/13   dcf     Created.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "com_dtypes.h"


/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Enumeration of available clocks for the uImage clock controller.
 */
typedef enum
{
  CLOCK_GCC_BLSP1_AHB_CLK,
  CLOCK_GCC_BLSP1_QUP1_APPS_CLK,
  CLOCK_GCC_BLSP1_QUP2_APPS_CLK,
  CLOCK_GCC_BLSP1_QUP3_APPS_CLK,
  CLOCK_GCC_BLSP1_QUP4_APPS_CLK,
  CLOCK_GCC_BLSP1_QUP5_APPS_CLK,
  CLOCK_GCC_BLSP1_QUP6_APPS_CLK,
  CLOCK_GCC_BLSP2_AHB_CLK,
  CLOCK_GCC_BLSP2_QUP1_APPS_CLK,
  CLOCK_GCC_BLSP2_QUP2_APPS_CLK,
  CLOCK_GCC_BLSP2_QUP3_APPS_CLK,
  CLOCK_GCC_BLSP2_QUP4_APPS_CLK,
  CLOCK_GCC_BLSP2_QUP5_APPS_CLK,
  CLOCK_GCC_BLSP2_QUP6_APPS_CLK,
  CLOCK_TOTAL_CLOCK_ENUMS,

}uClockIdType;

/*=========================================================================
      Function Definitions.
==========================================================================*/


/* ============================================================================
**  Function : uClock_EnableClock
** ============================================================================
*/
/**
  Enables a clock.
    
  @param[in]  eClockId  - The ID of the clock to enable.

  @return
  TRUE  - The clock was enabled.
  FALSE - Otherwise.
  
  @dependencies
  None.

*/

boolean uClock_EnableClock(uClockIdType eClockId);


/* ============================================================================
**  Function : uClock_DisableClock
** ============================================================================
*/
/**
  Disables a clock.
    
  @param[in]  eClockId  - The ID of the clock to disable.

  @return
  TRUE  - The clock was disabled.
  FALSE - Otherwise.
  
  @dependencies
  None.

*/

boolean uClock_DisableClock(uClockIdType eClockId);


/* ============================================================================
**  Function : uClock_IsClockEnabled
** ============================================================================
*/
/**
  Returns whether a clock is enabled or not.
    
  @param[in]  eClockId  - The ID of the clock to disable.

  @return
  TRUE  - The clock is on.
  FALSE - The clock is off.
  
  @dependencies
  None.

*/

boolean uClock_IsClockEnabled(uClockIdType eClockId);

#endif /* UCLOCK_H */
