/*
===========================================================================

FILE:         slimbus_bsp_data.c

DESCRIPTION:  This file implements the SLIMbus board support data.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/config/slimbus_adsp_8x26.c#1 $

when       who     what, where, why
--------   ---     -------------------------------------------------------- 
06/17/13   MJS     Update offset for new HWIO.
09/18/12   MJS     Initial revision for 8x26 ADSP.

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
    { 0x00, 0x00, 0xd0, 0x00, 0x17, 0x02 },
    "LPASS",
    0x0012f000,
    0xfe12f000,
    0xfe104000,
    11,
    12,
    0,
    { DAL_GPIO_CFG(70, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(71, 1, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA) },
    71,
    { 1, 1, 1 }
  }
};


