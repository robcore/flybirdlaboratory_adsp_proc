/*
===========================================================================

FILE:         slimbus_bsp_data.c

DESCRIPTION:  This file implements the SLIMbus board support data.

===========================================================================

                             Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/slimbus/config/slimbus_adsp_9x35.c#1 $

when       who     what, where, why
--------   ---     -------------------------------------------------------- 
03/25/14   MJS     Swap the GPIOs for 9x35.
08/19/13   MJS     Initial revision for 9x35 ADSP.

===========================================================================
             Copyright (c) 2013, 2014 Qualcomm Technologies Incorporated.
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
    { 0x00, 0x00, 0x00, 0x01, 0x17, 0x02 },
    "LPASS",
    0x001af000,
    0xfe1af000,
    0xfe184000,
    11,
    12,
    0,
    { DAL_GPIO_CFG(15, 6, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA),
      DAL_GPIO_CFG(14, 6, DAL_GPIO_INPUT, DAL_GPIO_KEEPER, DAL_GPIO_8MA) },
    14,
    { 1, 1, 1 }
  }
};


