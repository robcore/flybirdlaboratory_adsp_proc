#ifndef DIAG_LSM_H
#define DIAG_LSM_H
/*!
@ingroup diag_misc
  @file Diag_LSM.h 
  @brief
  Diagnostic Services API definitions specific to Windows devices

  This file contains APIs necessary to initialize Diagnostic services on 
  Windows devices. This additional initialization is necessary to support
  Diagnostic services on multiple process-spaces. On Windows phones, 
  Diagnostic Service API definitions are provided by the dynamic link library,
  Diag_LSM.dll.
  
  @note
  This file should be used only on QNX devices.
*/  

/*
Copyright (c) 2012-2013   by QUALCOMM Technologies, Incorporated. All Rights Reserved.
Qualcomm Confidential and Proprietary
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/api/services/Diag_LSM.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
01/25/13   sg      Added apis for f3 trace saving in lsm
01/26/11   rh      Removed windows specific declarations
08/30/10   mad     Modified comment for WINDIAG_TASK_INIT_COMPLETE_EVT_NAME
06/02/10   mad     Doxygenated
10/05/09   mad     Added Event to announce completion of Diag initialization.
                   This can be used by msgoutput driver to switch Debug output
                   to QXDM.
05/10/09   as      Extended the scope of extern to include Diag_LSM_DeInit
01/10/09   as      Fixed extern for __cplusplus 
07/07/09   mad     Included comdef.h
12/02/08   mad     Changed function description for device-driver model diag
02/04/08   mad     Added declarations for Diag_LSM_Init and DeInit functions
                   to enable diag clients to call these directly.
                   Moved IDiagPkt handle declaration to an internal header 
                   file, Diag_LSMi.h
11/29/07   mad     Created File
===========================================================================*/

#include "comdef.h" /* for byte and boolean */

/*!
@defgroup diag_misc Miscellaneous Diagnostic Service interfaces
This module describes some miscellaneous interfaces to diagnostic services.
*/

/*!
@ingroup diag_misc
Name of Windows synchronization event that clients can wait on, to get 
notification that Diag is ready for use. Clients that come up earlier in the
boot-up sequence can wait on this event, before calling Diag_LSM_Init() or 
using other Diag APIs. 
 
Clients need to obtain event HANDLE with the flag settings given as follows:
CreateEvent(NULL, FALSE, FALSE, WINDIAG_TASK_INIT_COMPLETE_EVT_NAME);
*/
#define WINDIAG_TASK_INIT_COMPLETE_EVT_NAME    "Windiag_Task_Initialized"

/*!
@ingroup diag_misc
@brief
   Initializes the Diag API Layer for the client process-space

   @param[in] *pParam  Not used. Place-holder for any future parameters.
   
   @dependencies
   Successful initialization requires Diag driver (windiag.dll) to be loaded 
   and available in the system.

   @return
   <ul>
      <li> FALSE - Initialization of Diag API layer failed
      <li> TRUE  - Initialization of Diag API layer succeeded
   </ul>

   @sideeffects
   None

   @sa
   Diag_LSM_DeInit

   @note
   Clients should call Diag_LSM_DeInit() to clean-up the memory structures on exit, 
   to avoid memory leaks.
*/
#ifdef __cplusplus
extern "C" {
#endif
boolean Diag_LSM_Init (byte* pParam);

/*!
@ingroup diag_misc
@brief
   De-Initialize the Diag API layer for the client process-space.
   This function should be called, to re-claim memory allocated in Diag_LSM_Init().

   @dependencies
   None

   @return
   <ul>
      <li> FALSE - De-initialization of Diag API layer failed
      <li> TRUE  - De-initialization of Diag API layer succeeded
   </ul>

   @sideeffects
   None

   @sa
   Diag_LSM_Init
*/
boolean Diag_LSM_DeInit(void);

boolean diag_enable(void);
boolean diag_disable(void);
/*!
@ingroup diag_misc
@brief
   Initializes the circular buffer for F3 trace saving in client's process space 
   @param[in]
    address: starting address of the circualr buffer that should be used to store the f3 messages.
	Note: Client needs to allocate the memory space for the buffer in the process space.
	length : length of the buffer
   @dependencies
   None
   
   @return
   <ul>
      <li> FALSE - Initialization of circular buffer indices  failed
      <li> TRUE  - Initialization of circular buffer indices succeeded
   </ul>

   @sideeffects
   None

   @sa
   Diag_LSM_Init
*/
boolean diag_lsm_f3_trace_init(uint8 * address,unsigned int length);


/*!
@ingroup diag_misc
@brief
  Initializes the control mask configuration for F3 trace.It is assumed it will only be
  called from serialized init functions (rcinit).Control mask is a bit mask which controls the kinds of diagnostic output that is saved by the feature.
  The bits for this mask are defined in the following table:

  Bit Position	Functionality
   7	        Reserved
   6	        Reserved
   5	        Reserved
   4	        Reserved
   3	        Enable Diag Mask Debug Mode* (see below)
   2	        Enable Diagnostic event saving deprecated
   1	        Reserved
   0	        Enable F3 message saving
  The most commonly used and recommended settings are:
   0x0 : Disable F3 message saving
   0x1 : Enable F3 message saving

  Diag Mask Debug Mode
   The "Diag Mask Debug Mode" is a special diagnostic mode which forces the F3 trace saving feature to use the internal QXDM/DIAG masks to filter messages, rather than the values from the Diag Debug Detail mask .
   This mode should NOT be used in normal AST testing scenarios, and should only be activated if requested by development teams. 
   It can be helpful in isolating bottlenecks in the F3 trace functionality by allowing more filtering options .
   Note that enabling this bit requires a QXDM connection so that the various masks can be communicated from QXDM to DIAG.
   If QXDM is not connected when this bit is enabled then the filtering behavior is dictated by whatever defaults are in place in the DIAG code.

   @dependencies
   None

   @return
   None 

   @sideeffects
   None

   @sa
   
*/

void diag_lsm_f3_trace_init_control_mask_config(uint8 control);


/*!
@ingroup diag_misc
@brief
  Initializes the detail mask configuration for F3 trace.It is assumed it will only be
  called from serialized init functions (rcinit).Diag Debug Detail is an 8-bit bit mask (where bit 0 is Least Significant Bit) which controls the levels of detail of the saved F3 trace.
  If a bit is set to 1, the information associated with that bit is saved to the buffer. The details of the bit mask are given in the table below.
  Custom MSG levels are not supported by F3 trace...only the legacy MSG levels listed below are recognized.

  Bit Position	Information Saved in Buffer
   7	            MSG_FATALs
   6	            MSG_ERRORs
   5	            MSG_HIGHs
   4	            MSG_MEDs
   3	            MSG_LOWs
   2	            Reserved
   1	            Timestamp
   0	            F3 arguments

   @dependencies
   None

   @return
   None 

   @sideeffects
   None

   @sa
   
*/
void diag_lsm_f3_trace_init_detail_mask_config(uint8 detail);


/*!
@ingroup diag_misc
@brief
   De-Initialize the Diag F3 Trace buffer for the client process-space.
   
   @dependencies
   None

   @return
   <ul>
      <li> FALSE - De-initialization of Diag F3 Trace buffer failed
      <li> TRUE  - De-initialization of Diag F3 Trace buffersucceeded
   </ul>

   @sideeffects
   None

   @sa
   Diag_LSM_F3_Trace_Init
*/
boolean diag_lsm_f3_trace_deinit(void);
#ifdef __cplusplus
}
#endif

#endif /* DIAG_LSM_H */
