/*
===========================================================================

FILE:         slimbus_bsp_data.c

DESCRIPTION:  This file implements the SLIMbus board support data.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/config/slimbus_adsp_9x25.c#1 $

when       who     what, where, why
--------   ---     -------------------------------------------------------- 
04/09/14   MJS     Swap GPIOs for 9x25.
06/17/13   MJS     Update offset for new HWIO.
09/20/12   MJS     Initial revision for 9x25 ADSP.

===========================================================================
             Copyright (c) 2012, 2013, 2014 Qualcomm Technologies Incorporated.
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
    { 0x00, 0x00, 0x80, 0x00, 0x17, 0x02 },
    "LPASS",
    0x0012f000,
    0xfe12f000,
    0xfe104000,
    11,
    12,
    0,
    { DAL_GPIO_CFG(15, 6, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(14, 6, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA) },
    14,
    { 1, 1, 1 }
  }
};


