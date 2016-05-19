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
$Header: //components/rel/core.adsp/2.6.1/power/mpm/config/asic/8084/MPMIntDevCfgData.c#1 $
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
  { MPM_TRIGGER_RISING_EDGE,   1,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,   5,              MPM_GPIO },
  /*5*/
  { MPM_TRIGGER_RISING_EDGE,   8,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,   9,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  28,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  34,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  40,              MPM_GPIO },
  /*10*/
  { MPM_TRIGGER_RISING_EDGE,  44,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  48,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  52,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  55,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  56,              MPM_GPIO },
  /*15*/
  { MPM_TRIGGER_RISING_EDGE,  58,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  60,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  64,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  67,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  68,              MPM_GPIO },
  /*20*/
  { MPM_TRIGGER_RISING_EDGE,  69,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  76,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  77,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  78,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  79,              MPM_GPIO },
  /*25*/
  { MPM_TRIGGER_RISING_EDGE,  84,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE,  95,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 102,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 103,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 104,              MPM_GPIO },
  /*30*/
  { MPM_TRIGGER_RISING_EDGE, 105,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 107,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 109,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 111,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 113,              MPM_GPIO },
  /*35*/
  { MPM_TRIGGER_RISING_EDGE, 121,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 122,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 123,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 131,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  /*40*/
  { MPM_TRIGGER_RISING_EDGE, 139,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, 141,              MPM_GPIO },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  /*45*/
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_RISING_EDGE, MPM_UNMAPPED_INT, MPM_IRQ  },
  /*50*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  /*55*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  /*60*/
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  { MPM_TRIGGER_LEVEL_HIGH,  MPM_UNMAPPED_INT, MPM_IRQ  },
  /*64 - End of the table entry */
  { MPM_TRIGGER_LEVEL_HIGH,      MPM_UNMAPPED_INT, MPM_EOT  },
};
