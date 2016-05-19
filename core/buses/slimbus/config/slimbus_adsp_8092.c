/*
===========================================================================

FILE:         slimbus_bsp_data.c

DESCRIPTION:  This file implements the SLIMbus board support data.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/config/slimbus_adsp_8092.c#1 $

when       who     what, where, why
--------   ---     -------------------------------------------------------- 
06/17/13   MJS     Update offset for new HWIO.
10/17/12   MJS     Updated GPIO numbers.
09/18/12   MJS     Initial revision for 8974 ADSP.

===========================================================================
             Copyright (c) 2012, 2013 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================
*/

#include "DALSys.h"
#include "HALhwio.h"
#include "SlimBus.h"
#include "DDITlmm.h"


/* Slimbus BSP data */
SlimBusBSPType SlimBusBSP[] =
{
  {
    2,
    "SLIMBUS",
    { 0x00, 0x00, 0xc0, 0x00, 0x17, 0x02 },
    "LPASS",
    0x001af000,
    0xfe1af000,
    0xfe184000,
    11,
    12,
    0,
    { DAL_GPIO_CFG(43, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(44, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA) },
    44,
    { 1, 1, 1 }
  }
};


