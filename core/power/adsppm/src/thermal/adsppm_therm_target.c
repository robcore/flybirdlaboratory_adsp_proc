/*============================================================================
  @file therm_target.c

  Target processor specific thermal code.
  
 
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

============================================================================*/
/*=======================================================================
$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/thermal/adsppm_therm_target.c#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
========================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "comdef.h"
#include "adsppm_therm_npa_mitigate.h"
#include "DALSys.h"

/*=======================================================================

                  STATIC MEMBER / FUNCTION DECLARATIONS / DEFINITIONS

========================================================================*/

/*=======================================================================

                  GLOBAL DEFINITIONS

========================================================================*/
/* List of all resources to be created for this target processor.
   Must defined for each target processor. */
const char *adsppm_therm_monitor_res_avail[] =
{
  "/therm/mitigate/cpuv_restriction"
};

/* Array size of adsppm_therm_monitor_res_avail[] to be used by common thermal
   SW. Must defined for each target processor. */
const unsigned int adsppm_therm_monitor_res_count = ARR_SIZE(adsppm_therm_monitor_res_avail);

/* Thermal task info struct */
//extern rex_tcb_type thermal_tcb;

/*=======================================================================

                  LOCAL FUNCTION DEFINITIONS

========================================================================*/

/*=======================================================================

                 PUBLIC FUNCTION DEFINITIONS

========================================================================*/
/**
  @brief adsppm_therm_target_init
 
  Initializes target specific thermal SW.
 
*/
void adsppm_therm_target_init(void)
{
  adsppm_therm_npa_mitigate_init();
}




