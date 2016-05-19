/*
===========================================================================
*/
/**
  @file uClock.c
  @brief Public definitions include file for accessing the uClock device driver.
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

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.  
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================

  $Header: //components/rel/core.adsp/2.6.1/systemdrivers/clock/hw/msm8994/src/uClock.c#1 $
  $DateTime: 2014/10/16 12:45:40 $
  $Author: pwbldsvc $

  when       who     what, where, why
  --------   ---     ---------------------------------------------------------- 
  12/17/13   dcf     Added for MSM8994 micro sensors functionality.

  ===========================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "com_dtypes.h"
#include "uClock.h"
#include "uClockHWIO.h"
#include "HALhwio.h"
#include "qurt.h"
#include "busywait.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/*
 * Micro-Clock state context structure.
 * Parameters:
 *   Mutex             - Synchronization mutex locking.
 *   bInitialized      - Specifies if initialization has taken place.
 *   anClockReferences - Array of clock references.
 */
typedef struct
{
   qurt_mutex_t Mutex;
   boolean      bInitialized;
   uint32       anClockReferences[CLOCK_TOTAL_CLOCK_ENUMS];

}uClockCtxtType;


/*=========================================================================
      Local Variables
==========================================================================*/

/*
 * Global Micro-Clock Driver Context.
 */
static uClockCtxtType uClockDriverCtxt;

/*=========================================================================
      Function Definitions.
==========================================================================*/

/* ============================================================================
**  Function : uClock_IsOn
** ============================================================================
*/
/**
  Internal API which returns whether a clock is on or not.
    
  @param[in]  eClockId  - The ID of the clock to enable.

  @return
  TRUE  - The clock is on.
  FALSE - Otherwise.
  
  @dependencies
  None.

*/
boolean uClock_IsOn(uClockIdType eClockId)
{
  uint32 nVal = 0;
    
  switch(eClockId)
  {
    case CLOCK_GCC_BLSP1_QUP1_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP1_QUP1_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP1_QUP2_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP1_QUP2_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP1_QUP3_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP1_QUP3_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP1_QUP4_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP1_QUP4_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP1_QUP5_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP1_QUP5_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP1_QUP6_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP1_QUP6_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_QUP1_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP2_QUP1_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_QUP2_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP2_QUP2_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_QUP3_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP2_QUP3_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_QUP4_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP2_QUP4_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_QUP5_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP2_QUP5_I2C_APPS_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_QUP6_APPS_CLK:
       nVal = HWIO_INF(GCC_BLSP2_QUP6_I2C_APPS_CBCR, CLK_OFF);
       break;
       
    case CLOCK_GCC_BLSP1_AHB_CLK:
       nVal = HWIO_INF(GCC_BLSP1_AHB_CBCR, CLK_OFF);
       break;

    case CLOCK_GCC_BLSP2_AHB_CLK:
       nVal = HWIO_INF(GCC_BLSP2_AHB_CBCR, CLK_OFF);
       break;
       
    default:
       break;
   }
   
   if(nVal != 0)
   {
     return(FALSE);
   }
   else
   {
     return(TRUE);
   }
   
} /* uClock_IsOn */


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

boolean uClock_EnableClock(uClockIdType eClockId)
{
    boolean bRetVal = TRUE;
    uint32 nTimeout = 150;
    
 //   if(uClockDriverCtxt.bInitialized == FALSE)
 //   {
 //     qurt_mutex_init(&uClockDriverCtxt.Mutex);
 //     uClockDriverCtxt.bInitialized = TRUE;
 //   }
    
   if(eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
   {
  //    qurt_mutex_lock(&uClockDriverCtxt.Mutex);

      if(uClockDriverCtxt.anClockReferences[eClockId] == 0)
      {
         switch(eClockId)
         {
            case CLOCK_GCC_BLSP1_QUP1_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP1_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP1_QUP2_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP2_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP1_QUP3_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP3_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP1_QUP4_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP4_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP1_QUP5_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP5_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP1_QUP6_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP6_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP2_QUP1_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP1_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP2_QUP2_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP2_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP2_QUP3_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP3_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP2_QUP4_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP4_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP2_QUP5_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP5_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP2_QUP6_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP6_I2C_APPS_CBCR, CLK_ENABLE, 0x1);
               break;

            case CLOCK_GCC_BLSP1_AHB_CLK:
               HWIO_OUTF(GCC_SPARE_CLOCK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA, 0x1);
               break;

            case CLOCK_GCC_BLSP2_AHB_CLK:
               HWIO_OUTF(GCC_SPARE_CLOCK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA, 0x1);
               break;

            default:
               bRetVal = FALSE;
               break;
         }
         
         while(uClock_IsOn(eClockId) != TRUE)
         {
           if(nTimeout == 0)
           {
             break;
           }
           busywait(2);
           nTimeout--;
         }

      }
      
      /*
       * Increase the reference count on this clock.
       */
      if(nTimeout != 0)
      {
        uClockDriverCtxt.anClockReferences[eClockId]++;
        bRetVal = TRUE;
      }
      else
      {
        bRetVal = FALSE;
      }
        
  //    qurt_mutex_unlock(&uClockDriverCtxt.Mutex);
      
      return(bRetVal);
   }
   
   return(FALSE);

} /* uClock_EnableClock */


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

boolean uClock_DisableClock(uClockIdType eClockId)
{
 //   if(uClockDriverCtxt.bInitialized == FALSE)
 //   {
 //     qurt_mutex_init(&uClockDriverCtxt.Mutex);
 //     uClockDriverCtxt.bInitialized = TRUE;
 //   }
    
   if(eClockId < CLOCK_TOTAL_CLOCK_ENUMS)
   {
 //     qurt_mutex_lock(&uClockDriverCtxt.Mutex);
      
      if(uClockDriverCtxt.anClockReferences[eClockId] > 0)
      {
        uClockDriverCtxt.anClockReferences[eClockId]--;
      }

      if(uClockDriverCtxt.anClockReferences[eClockId] == 0)
      {
         switch(eClockId)
         {
            case CLOCK_GCC_BLSP1_QUP1_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP1_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP1_QUP2_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP2_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP1_QUP3_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP3_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP1_QUP4_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP4_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP1_QUP5_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP5_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP1_QUP6_APPS_CLK:
               HWIO_OUTF(GCC_BLSP1_QUP6_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP2_QUP1_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP1_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP2_QUP2_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP2_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP2_QUP3_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP3_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP2_QUP4_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP4_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP2_QUP5_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP5_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP2_QUP6_APPS_CLK:
               HWIO_OUTF(GCC_BLSP2_QUP6_I2C_APPS_CBCR, CLK_ENABLE, 0x0);
               break;

            case CLOCK_GCC_BLSP1_AHB_CLK:
               HWIO_OUTF(GCC_SPARE_CLOCK_BRANCH_ENA_VOTE, BLSP1_AHB_CLK_ENA, 0x0);
               break;

            case CLOCK_GCC_BLSP2_AHB_CLK:
               HWIO_OUTF(GCC_SPARE_CLOCK_BRANCH_ENA_VOTE, BLSP2_AHB_CLK_ENA, 0x0);
               break;

            default:
               break;
         }
      }
      
 //     qurt_mutex_unlock(&uClockDriverCtxt.Mutex);
      return(TRUE);
   }
   
   return(FALSE);
   
} /* uClock_DisableClock */


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

boolean uClock_IsClockEnabled(uClockIdType eClockId)
{
   return(uClock_IsOn(eClockId));
   
} /* uClock_IsClockEnabled */

