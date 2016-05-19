#ifndef __UGPIOIntQdi_H
#define __UGPIOIntQdi_H
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

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/GPIOInt/inc/uGPIOIntQDI.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
1/1/2010   aratin  First draft created. 
===========================================================================*/
#include "qurt_qdi_constants.h"

/*=========================================================================

                           DATA DEFINITIONS

===========================================================================*/
#define UGPIOINT_QDI_MAP_UGPIOINT                 (0+QDI_PRIVATE)
#define UGPIOINT_QDI_SET_GPIO_CONFIG              (1+QDI_PRIVATE)
#define UGPIOINT_QDI_CLEAR_GPIO_CONFIG            (2+QDI_PRIVATE)
#define UGPIOINT_QDI_SET_MPM_TRIGGER              (3+QDI_PRIVATE)

#define UGPIOINT_QDI_TRUE                          0x00010
#define UGPIOINT_QDI_FALSE                         0x0               
#define UGPIOINT_QDI_ERROR                         -1
#define UGPIOINT_QDI_SUCCESS                       0

/*
 * Micro gpioint qdi layer driver name.
 */
#define uGPIOIntQdiName                            "/dev/uGPIOIntQdi"


#endif /*___UGPIOIntQdi_H*/
