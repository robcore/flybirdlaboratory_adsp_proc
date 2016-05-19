/*
===========================================================================

FILE:         HALspmmmap.c

DESCRIPTION:  
  This is the hardware abstraction layer for the SPM block which defines
  the memory map function to obtain base address for RIVA_SAW2.

===========================================================================

             Copyright © 2012 Qualcomm Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
===========================================================================

$Header: //components/rel/core.adsp/2.6.1/power/spm/src/hal/HALspmmmap.c#1 $

=============================================================================*/

/* -----------------------------------------------------------------------
**                           INCLUDES
** ----------------------------------------------------------------------- */
#include "spm.h"
#include "HALspmPlatform.h"
#include "DALDeviceId.h"
#include "DDIHWIO.h"

/* ==================================================================
                     GLOBAL DATA DECLARATIONS
   ================================================================== */
/**
 * Generating base address to send to HWIO 
 */
uint8 *g_spmBasePtrAddress USPM_DATA_SECTION = NULL;
#define SSTR(x) STR(x)
#define STR(x) #x

/* -----------------------------------------------------------------------
**                         FUNCTIONS
** ----------------------------------------------------------------------- */

/*
 * 
 * @brief spm_hwio_mmap
 * 
*/
void spm_hwio_mmap(void)
{
  static DalDeviceHandle *spmDALHandle;
  DALResult eResult;

  eResult = DAL_DeviceAttach(DALDEVICEID_HWIO, &spmDALHandle);
  if (eResult == DAL_SUCCESS)
  {
    DalHWIO_MapRegion(spmDALHandle, SSTR(SPM_BASE_NAME), &g_spmBasePtrAddress);
  }
}
