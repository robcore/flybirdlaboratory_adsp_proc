#ifndef HALSB_INTERNAL_H
#define HALSB_INTERNAL_H
/*
============================================================================

FILE:          HALsbInternal.h

DESCRIPTION:   HAL SB Internal header file.

                Copyright (c) 2010, 2011 Qualcomm Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
============================================================================

============================================================================
  EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.adsp/2.6.1/buses/slimbus/hw/v1/HALsbInternal.h#1 $

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2011-11-12  MJS  Remove references to DAL.
  2011-06-09  MJS  Add shadow register support.
  2010-07-26  ps   Initial version.
============================================================================
*/

/* ----------------------------------------------------------------------- 
** Includes
** ----------------------------------------------------------------------- */ 

#include "SlimBusTypes.h"
#include "HALhwio.h"    /* __inpdw() , __outpdw() macros */
#include "HALhwioSlimBus.h"   /* HWIO registers address , uMask and shift */
#include "HALsbTarget.h"      /* HAL SlimBus Target specific information */

/* ----------------------------------------------------------------------- 
** Constants  SB
** ----------------------------------------------------------------------- */ 

#define SB_HWIO_IN(base, hwiosym)                      __inpdw(base + SB_ADDR(hwiosym))                          
#define SB_HWIO_OUT(base, hwiosym, val)                __outpdw(base + SB_ADDR(hwiosym), (val))         
#define SB_HWIO_INI(base, hwiosym, index)              __inpdw(base + SB_ADDRn(hwiosym,index))
#define SB_HWIO_OUTI(base, hwiosym, index, val)        __outpdw(base + SB_ADDRn(hwiosym,index), (val))
                                                        
#define SB_HWIO_INS(base, shadow, hwiosym)                      (*(shadow))                          
#define SB_HWIO_OUTS(base, shadow, hwiosym, val)                (*(shadow)) = (val); __outpdw(base + SB_ADDR(hwiosym), (val))         
#define SB_HWIO_INSI(base, shadow, hwiosym, index)              (*(shadow))
#define SB_HWIO_OUTSI(base, shadow, hwiosym, index, val)        (*(shadow)) = (val); __outpdw(base + SB_ADDRn(hwiosym,index), (val))
                                                        
#define SB_HWIO_INM(base, hwiosym, mask)               ( SB_HWIO_IN((base), hwiosym) & (mask))
#define SB_HWIO_OUTM(base, hwiosym, mask, val)         SB_HWIO_OUT((base), hwiosym, ((SB_HWIO_IN((base), hwiosym) & (~(mask))) | ((val) & (mask))))
#define SB_HWIO_INMI(base, hwiosym, index, mask)       ( SB_HWIO_INI(base, hwiosym, index) & (mask))
#define SB_HWIO_OUTMI(base, hwiosym, index, mask, val) SB_HWIO_OUTI(base, hwiosym, index, ((SB_HWIO_INI(base, hwiosym, index) & (~(mask))) | ((val) & (mask))))

#define SB_HWIO_INSM(base, shadow, hwiosym, mask)               ( SB_HWIO_INS((base), (shadow), hwiosym) & (mask))
#define SB_HWIO_OUTSM(base, shadow, hwiosym, mask, val)         SB_HWIO_OUTS((base), (shadow), hwiosym, ((SB_HWIO_INS((base), shadow, hwiosym) & (~(mask))) | ((val) & (mask))))
#define SB_HWIO_INSMI(base, shadow, hwiosym, index, mask)       ( SB_HWIO_INSI((base), (shadow), hwiosym, index) & (mask))
#define SB_HWIO_OUTSMI(base, shadow, hwiosym, index, mask, val) SB_HWIO_OUTSI((base), (shadow), hwiosym, index, ((SB_HWIO_INSI((base), (shadow), hwiosym, index) & (~(mask))) | ((val) & (mask))))

#define SB_HWIO_INF(base, hwiosym, field)               ( (SB_HWIO_IN((base), hwiosym) & SB_BSMSK(hwiosym,field))>>SB_SHFT(hwiosym,field))
#define SB_HWIO_OUTF(base, hwiosym, field, val)         SB_HWIO_OUT((base), hwiosym, ((SB_HWIO_IN((base), hwiosym) & (~(SB_BSMSK(hwiosym,field)))) | ((val<<SB_SHFT(hwiosym,field)) & (SB_BSMSK(hwiosym,field)))))
#define SB_HWIO_INFI(base, hwiosym, index, field)       ( (SB_HWIO_INI((base), hwiosym , index) & SB_BSMSK(hwiosym,field))>>SB_SHFT(hwiosym,field))
#define SB_HWIO_OUTFI(base, hwiosym, index, field, val) SB_HWIO_OUTI((base), hwiosym, index, ((SB_HWIO_INI((base), hwiosym,index) & (~(SB_BSMSK(hwiosym,field)))) | ((val<<SB_SHFT(hwiosym,field)) & (SB_BSMSK(hwiosym,field)))))

#define SB_HWIO_INSF(base, shadow, hwiosym, field)               ( (SB_HWIO_INS((base), (shadow), hwiosym) & SB_BSMSK(hwiosym,field))>>SB_SHFT(hwiosym,field))
#define SB_HWIO_OUTSF(base, shadow, hwiosym, field, val)         SB_HWIO_OUTS((base), (shadow), hwiosym, ((SB_HWIO_INS((base), (shadow), hwiosym) & (~(SB_BSMSK(hwiosym,field)))) | ((val<<SB_SHFT(hwiosym,field)) & (SB_BSMSK(hwiosym,field)))))
#define SB_HWIO_INSFI(base, shadow, hwiosym, index, field)       ( (SB_HWIO_INSI((base), (shadow), hwiosym , index) & SB_BSMSK(hwiosym,field))>>SB_SHFT(hwiosym,field))
#define SB_HWIO_OUTSFI(base, shadow, hwiosym, index, field, val) SB_HWIO_OUTSI((base), (shadow), hwiosym, index, ((SB_HWIO_INSI((base), (shadow), hwiosym,index) & (~(SB_BSMSK(hwiosym,field)))) | ((val<<SB_SHFT(hwiosym,field)) & (SB_BSMSK(hwiosym,field)))))

#endif  /* HALSB_INTERNAL_H */
