#ifndef HALSB_TARGET_H
#define HALSB_TARGET_H
/*
============================================================================

FILE:          HALsbTarget.h

DESCRIPTION:   HAL SB Internal target specific header file.

                Copyright (c) 2011 Qualcomm Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
============================================================================

============================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/buses/slimbus/hw/v1/HALsbTarget.h#1 $

when       who     what, where, why
--------   ---     --------------------------------------------------------
06/09/11   MJS     Add shadow register support.
05/11/11   MJS     Initial revision.

============================================================================
*/

/* ----------------------------------------------------------------------- 
** Includes
** ----------------------------------------------------------------------- */ 
#include "HALhwioSlimBus.h"   /* HWIO registers address , uMask and shift */

/* ----------------------------------------------------------------------- 
** Constants  SB
** ----------------------------------------------------------------------- */ 
#define SB_ADDR(hwiosym)        HWIO_SB_##hwiosym##_ADDR
#define SB_ADDRn(hwiosym,index) HWIO_SB_##hwiosym##_ADDR(index)
#define SB_BSMSK(hwiosym,field) HWIO_SB_##hwiosym##_##field##_BMSK
#define SB_SHFT(hwiosym,field)  HWIO_SB_##hwiosym##_##field##_SHFT
#define SB_MAXn(hwiosym)        HWIO_SB_##hwiosym##_MAXn

#define HAL_SB_MAX_HANDLES 1

#endif  /* HALSB_TARGET_H */
