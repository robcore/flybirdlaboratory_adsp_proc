/**
@file coremain.c
@brief This file contains the implementation details for ...
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2013 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/task/src/coremain.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
===============================================================================*/

// *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK*
// *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK*

#ifndef COREMAIN_EXCLUDE_KERNEL_HACK
#ifndef COREMAIN_EXCLUDE_MAIN
#ifdef GUEST_OS_MULTI_PD_FLAVOR
#ifdef LPASS_SENSOR_IMG

// THIS IS NOT AN DEBUGTOOLS DELIVERABLE. DEBUGTOOLS TEAM DOES NOT
// SUPPORT NOR MAINTAIN KERNEL CONFIGURATION THROUGH GLOBAL VARIABLES.
// THE KERNEL MUST CONFIGURE THEIR SOFTWARE PACKAGES APPROPRIATELY PER
// IMAGE. PUT THIS HACK IN $SUB$$MAIN$() WHICH CALLS $SUPER$$MAIN()
// WHICH IS THE MAIN() IN THIS MODULE.

 unsigned int heapSize=0x40000;   // The heap size needs to be defined for user pd in main. The heapsize is weak symbol from qurt
                                  // This needs to be defined until xml support for user pd comes into picture, as the kernel team
                                  // does not manage their deliverable configuration.

#endif // LPASS_SENSOR_IMG
#endif // GUEST_OS_MULTI_PD_FLAVOR
#endif // COREMAIN_EXCLUDE_MAIN
#endif

// *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK*
// *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK* *HACK*

#include "rcinit_dal.h"
#include "qurt.h"

void bootstrap_exception_handler(void); // forward reference
void bootstrap_rcinit_task(void); // forward reference

/*===========================================================================
FUNCTION COREMAIN_MAIN

DESCRIPTION
  Bootstrap the context for error processing
  Bootstrap the context for rcinit processing

DEPENDENCIES
  None

RETURN VALUE
  None, this routine returns at the completion of rcinit startup processing
  to facilitate other images being able to initialize corebsp and then regain
  control of the context following the rcinit startup process.

SIDE EFFECTS
  None

===========================================================================*/
void coremain_main(void)
{
   DALSYS_InitMod(NULL);               // no error return

   bootstrap_exception_handler();      // creates context for error processing

   bootstrap_rcinit_task();            // creates context for rcinit processing
}

/*===========================================================================
FUNCTION MAIN

DESCRIPTION
  Bootstrap the context for core_main through call to rex_init

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
#if 0
int main(void)
{
   DALSYSEventHandle hEvent;

   coremain_main(); // when main is not delivered here, this is the entry to start cbsp

   // Block Forever

   if ((DAL_SUCCESS == DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEvent, NULL)) &&
       (DAL_SUCCESS == DALSYS_EventWait(hEvent)))
   {
      for (;;) /* NULL */ ;
   }

   else
   {
      for (;;) /* NULL */ ;
   }

   /* NOTREACHED */

   return (0);
}
#endif
