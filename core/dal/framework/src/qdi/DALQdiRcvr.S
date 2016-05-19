/*======================================================================

               DALQdiRcvr.S

GENERAL DESCRIPTION
		  QDI DAL FORWARDING FUNCTIONS in QURTOS 
			
EXTERNAL FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS
   None.

      Copyright (c) 2012
                    by Qualcomm Technologies Incorporated.  All Rights Reserved.

========================================================================*/

/*======================================================================

                        EDIT HISTORY FOR MODULE

 This section contains comments describing changes made to the module.
 Notice that changes are listed in reverse chronological order.


$Header: //components/rel/core.adsp/2.6.1/dal/framework/src/qdi/DALQdiRcvr.S#1 $
$DateTime: 2014/10/16 12:45:40 $

when       who     what, where, why
--------   ---     -----------------------------------------------------
06/08/12   aa      Updated for QDI2.0.
06/01/12   aa      Tuned for DAL, Bug fix and added comments for release.
04/03/12   jack    Initial Version
========================================================================*/
/*
   A QDI forwarding object in QURTOS looks like this:

   QDIForwardingObject:
     invoke    == points at dal_fwd_invoker.
     dalHandle == stores the guestOS DalDeviceHandle to which 
                  we forward the DDI calls.
     qdiHandle == stores the QDI handle we're mapped to.

*/
#include "qurt_qdi_constants.h"

	.equ QDI_DAL_FWD, 128                          /* 0-128 method id reserved for QDI FW */
   
	.text
	.global dal_fwd_invoker
 .type   dal_fwd_invoker, @function
   
dal_fwd_invoker:
	{
	p0 = !cmp.gt(r2,#QDI_DAL_FWD-1)                /* Is it a non-DAL method? */
	if (p0.new) jump:nt ##qurt_qdi_method_default
	}
dal_fwd_invoker_normal:
	{
	r14 = add(r2,#-QDI_DAL_FWD)		              /* Get dal vtable index */
	r0 = memw(r1+#12)			                       /* Get DalDeviceHandle in QURTOS, 12 bytes offset(qdi_obj_t)  */
	r7:6 = C1:0			                             /* Restore r7,r6 from loopcounter pair register argument from userland */
	}
   {
	r15 = memw(r0+#4)			                       /* Fetch vtable pointer from handle */
   r2 = r7                                        /* Restore r2 from r7 */
   r1 = r6                                        /* Restore r1 from r6 */
   }

/* TBD -- to be secure, we should check that the vtable index in R14 
 * does not exceed the number of entries in the guest OS vtable... 
 */

	r14 = memw(r15+r14<<#2)			                 /* Base Addr + index*4; Fetch vtable entry */
	jumpr r14                                      /* Invoke Driver method */

 .size dal_fwd_invoker, .-dal_fwd_invoker

   
   