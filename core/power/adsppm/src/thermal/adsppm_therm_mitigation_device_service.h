#ifndef ADSPPM_THERM_MITIGATION_DEVICE_SERVICE_H
#define ADSPPM_THERM_MITIGATION_DEVICE_SERVICE_H

/*============================================================================
  FILE:         therm_npa_mitigate.h
  
  OVERVIEW:     Thermal NPA mitigation resources header file.
 
            
* Copyright (c) 2013 Qualcomm Technologies, Inc.
* All Rights Reserved.
* Qualcomm Technologies, Inc. Confidential and Proprietary.

============================================================================*/
/*=======================================================================
$Header: //components/rel/core.adsp/2.6.1/power/adsppm/src/thermal/adsppm_therm_mitigation_device_service.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "comdef.h"

/*
===============================================================================

                             TYPE DEFINITION(S)

===============================================================================
*/

/*
===============================================================================

                           GLOBAL FUNCTION DECLARATIONS

===============================================================================
*/

/**
 * @brief Initialization function for the Thermal QMI service
 *
 * This function implements the initialization code for the 
 * Thermal QMI service 
 */
void adsppm_therm_qmi_init(void);


#endif /* ADSPPM_THERM_MITIGATION_DEVICE_SERVICE_H */
