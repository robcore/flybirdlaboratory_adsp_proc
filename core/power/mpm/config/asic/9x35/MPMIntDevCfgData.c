/*==============================================================================
   FILE:        MPMIntDevCfgData.c

  OVERVIEW:     MPM hardware to local interrupt/gpio mapping info. This
                mapping is target specific and may change for different 
                targets. Even mapping could change between masters within a
                same target as some master may want a mapped irq as wakeup
                interrupt while other may not.
 
  DEPENDENCIES: None

                Copyright (c) 2013 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/mpm/config/asic/9x35/MPMIntDevCfgData.c#1 $
$DateTime: 2014/10/16 12:45:40 $
=============================================================================*/ 

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "vmpm_internal.h"

/* -----------------------------------------------------------------------
**                           DATA
** ----------------------------------------------------------------------- */

/**
 * Table mapping the MPM Pin number to the GPIO and/or IRQ pin 
 * number per the IP Catalog. 
 */
mpm_int_pin_mapping_type devcfg_MpmInterruptPinNum_Mapping[] =
{
  /* Trigger                 Local Pin#         Pin Type   */
  /* -------                 -------------      --------   */
  /*0*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_OPEN },
  { MPM_TRIGGER_RISING_EDGE, 80              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 0               , MPM_GPIO },
  /*5*/
  { MPM_TRIGGER_RISING_EDGE, 1               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 2               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 3               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 4               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 5               , MPM_GPIO },
  /*10*/
  { MPM_TRIGGER_RISING_EDGE, 6               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 7               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 8               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 9               , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 10              , MPM_GPIO },
  /*15*/
  { MPM_TRIGGER_RISING_EDGE, 11              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 12              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 13              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 14              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 15              , MPM_GPIO },
  /*20*/
  { MPM_TRIGGER_RISING_EDGE, 16              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 17              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 18              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 19              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 20              , MPM_GPIO },
  /*25*/
  { MPM_TRIGGER_RISING_EDGE, 21              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 24              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 25              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 51              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 81              , MPM_GPIO },
  /*30*/
  { MPM_TRIGGER_RISING_EDGE, 62              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 63              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 64              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 65              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 66              , MPM_GPIO },
  /*35*/
  { MPM_TRIGGER_RISING_EDGE, 67              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 43              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 50              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 53              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 54              , MPM_GPIO },
  /*40*/
  { MPM_TRIGGER_RISING_EDGE, 55              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, 56              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 82              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_GPIO },
  /*45*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, 77              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  /*50*/
  { MPM_TRIGGER_RISING_EDGE, 83              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 84              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 85              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 58              , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  /*55*/
  { MPM_TRIGGER_RISING_EDGE, 59              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 60              , MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 68              , MPM_GPIO },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, 70              , MPM_GPIO },
  /*60*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_OPEN },
  /*64 - End of the table entry */
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_EOT  },
};
