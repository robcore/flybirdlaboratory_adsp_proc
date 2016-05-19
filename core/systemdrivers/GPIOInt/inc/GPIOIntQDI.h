#ifndef __GPIOIntQdi_H
#define __GPIOIntQdi_H
/*===========================================================================

  G P I O   I N T E R R U P T   C O N T R O L L E R  Q D I   W R A P P E R  

DESCRIPTION
  This modules contains the Qurt Driver Invocation (QDI) layer that interfaces
  with the driver in the kernel on behalf of the user clients in the user domain.

REFERENCES

       Copyright (c) 2012 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/inc/GPIOIntQDI.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "qurt_qdi_constants.h"
#include "DDIGPIOInt.h"
/*=========================================================================

                           DATA DEFINITIONS

===========================================================================*/
#define GPIOINT_QDI_REGISTER                      (0+QDI_PRIVATE)
#define GPIOINT_QDI_DEREGISTER                    (1+QDI_PRIVATE)
#define GPIOINT_QDI_INTERRUPT_RECEIVE             (2+QDI_PRIVATE)
#define GPIOINT_QDI_SET_TRIGGER                   (3+QDI_PRIVATE)  
#define GPIOINT_QDI_IS_INTERRUPT_SET              (4+QDI_PRIVATE) 
#define GPIOINT_QDI_IS_INTERRUPT_PENDING          (5+QDI_PRIVATE) 
#define GPIOINT_QDI_IS_INTERRUPT_ENABLED          (6+QDI_PRIVATE)  
#define GPIOINT_QDI_CLEAR_INTERRUPT               (7+QDI_PRIVATE)  
#define GPIOINT_QDI_CREATE_SIGNAL                 (8+QDI_PRIVATE)
#define GPIOINT_QDI_TRIGGER_INTERRUPT             (9+QDI_PRIVATE)
#define GPIOINT_QDI_SET_MAX_GPIOS                (10+QDI_PRIVATE)
#define GPIOINT_QDI_CLEAR_SIGNAL                 (11+QDI_PRIVATE)
#define GPIOINT_QDI_SET_SIGNAL                   (12+QDI_PRIVATE)
#define GPIOINT_QDI_SIGNAL_RECEIVE               (13+QDI_PRIVATE)
#define GPIOINT_QDI_DESTROY_SIGNAL               (14+QDI_PRIVATE)

#define GPIOINT_QDI_INTERRUPT_SIGNAL              0x10
#define GPIOINT_QDI_TASK_START                    0x00008000
#define GPIOINT_QDI_TASK_STOP                     0x00010000  
#define GPIOINT_QDI_TRUE                          0x00010
#define GPIOINT_QDI_FALSE                         0x0               
#define GPIOINT_QDI_ERROR                         -1
#define GPIOINT_QDI_SUCCESS                       0

#define GPIOIntQdiName                            "/dev/GPIOIntQdi"

static __inline DALResult
GPIOInt_DisableGPIOInterrupt(DalDeviceHandle * _h, uint32 gpio)
{
   if(DALISREMOTEHANDLE(_h))
   {
      DalRemoteHandle *hRemote = (DalRemoteHandle *)DALPREPREMOTEHANDLE(_h);
      return hRemote->pVtbl->FCN_0(DALVTBLIDX(((GPIOIntHandle *)_h)->pVtbl, DisableInterrupt ), _h, gpio);
   }
   return ((GPIOIntHandle *)_h)->pVtbl->DisableGPIOInterrupt( _h, gpio);
}

static __inline DALResult
GPIOInt_EnableGPIOInterrupt(DalDeviceHandle * _h, uint32 gpio)
{
   if(DALISREMOTEHANDLE(_h))
   {
      DalRemoteHandle *hRemote = (DalRemoteHandle *)DALPREPREMOTEHANDLE(_h);
      return hRemote->pVtbl->FCN_0(DALVTBLIDX(((GPIOIntHandle *)_h)->pVtbl, EnableInterrupt ), _h, gpio);
   }
   return ((GPIOIntHandle *)_h)->pVtbl->EnableGPIOInterrupt( _h, gpio);
}
#endif /*___GPIOIntQdi_H*/
