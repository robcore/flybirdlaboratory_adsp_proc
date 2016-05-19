/*==========================================================================
ELite Source File

This file implements the setting of custom static CAPI modules into 
the audio modules database.

Copyright (c) 2013 QUALCOMM Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
=========================================================================== */

/*===========================================================================
Edit History

when       who     what, where, why
--------   ---     ---------------------------------------------------------
06/10/13   DS      Created file
=========================================================================== */

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "adsp_error_codes.h"
#include "qurt_elite_diag.h"

/* This file will get generated at compile time when custom_capi_integration.py 
   is called from hap_audencdec.scons file.
*/
#include "custom_AudioDecSvc_Util.h"

/*---------------------------------------------------------------------------
 * Definitions
 * -------------------------------------------------------------------------*/
#define SIZE_OF_ARRAY(a) (sizeof(a)/sizeof((a)[0]))

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/* ================================================================================================
 * Function Name :  hap_adsp_amdb_add_static_capi
 *
 * Purpose		 :	To add custom static CAPI modules to the audio module database.
 *
 * Description	 :  This function will add the custom CAPI modules to the AMDB database.
 *					Follow below step to add custom static CAPI modules to AMDB data base
 *					-> Add "capi_module_definition_t" information to "custom_capi_module_definitions"
 *
 * Input		 :	None
 *
 * Output		 :  result
 * ================================================================================================*/
ADSPResult hap_adsp_amdb_add_static_capi(void)
{
   ADSPResult result = ADSP_EOK;

   /* Adding custom CAPI modules to the AMDB.
      Here it will add all the modules to the AMDB that are present in "custom_capi_module_definitions" table.
   */
   for (uint32_t i = 0; i < SIZE_OF_ARRAY(custom_capi_module_definitions); i++)
   {
      ADSPResult errCode = adsp_amdb_add_static_capi(custom_capi_module_definitions[i].media_fmt_id,
            custom_capi_module_definitions[i].getsize_f,
            custom_capi_module_definitions[i].ctor_f);
      if(ADSP_FAILED(errCode))
      {
         MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Failed to add custom static module %lu", custom_capi_module_definitions[i].media_fmt_id);
      }
   }

   return result;
}
