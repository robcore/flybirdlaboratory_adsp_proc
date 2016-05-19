/*==========================================================================
File: custom_audproc_db_if.cpp

Source file for implementing addition of custom static topologies and modules into 
the topology and  audio modules databases.

Copyright (c) 2013 QUALCOMM Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
=========================================================================== */

/*===========================================================================
Edit History

when       who     what, where, why
--------   ---     ---------------------------------------------------------
03/20/13   DS      Created file
06/10/13   DS	   Comments updated
=========================================================================== */

/*---------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
/* These files will get generated at compile time when custom_audio_integration.py 
   is called from hap_audproc.scons file.
*/
#include "custom_adsp_audproc_api.h"
#include "custom_audproc_appi_topo.h"
#include "custom_audproc_db_if.h"

/*---------------------------------------------------------------------------
 * Definitions
 * -------------------------------------------------------------------------*/
#define SIZE_OF_ARRAY(a) (sizeof(a)/sizeof((a)[0]))

/*---------------------------------------------------------------------------
 * Function Definitions
 * -------------------------------------------------------------------------*/

/* ================================================================================================
 * Function Name :  hap_AddCustomStaticTopologiesAndModules
 *
 * Purpose		 :	To add custom static topologies and modules to the database.
 *
 * Description	 :  This function will add the all types of custom static toplogies
 *					to the topology database and it also add the custom modules to 
 *					the AMDB.
 *					Follow below step to add custom static topologies to topology data base
 *					-> Create "audproc_topology_definition_t" like "popp_gain_ctrl_def" and 
 *					   add it to one of the custom topology types.(POPP, POPREP, COPP, COPREP)
 *					Follow below step to add custom static modules to AMDB.
 *					-> Add "module_definition_t" information to "audproc_custom_module_definitions"
 *
 * Input		 :	None
 *
 * Output		 :  result
 * ================================================================================================*/
ADSPResult hap_AddCustomStaticTopologiesAndModules(void)
{
   ADSPResult result;

   /*---------------------------------------------------------------------------
    * Add custom static topologies to the topology database
    * -------------------------------------------------------------------------*/

   /* Adding custom static toplogy of type POPP to the topology database.
      Here "topo_db_add_internal_topologies()" API is used to add "audproc_custom_static_topos_popp" topologies to the topology database, in which
	  the topology ID will be validated.
   */
   result = topo_db_add_internal_topologies(DYNA_SVC_PP_TYPE_POPP, SIZE_OF_ARRAY(audproc_custom_static_topos_popp), audproc_custom_static_topos_popp);
   if (ADSP_FAILED(result))
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Failed to add Custom POPP topologies with %d", result);
      return result;
   }

   /* Adding custom static toplogy of type POPREP to the topology database.
      Here "topo_db_add_internal_topologies()" API is used to add "audproc_custom_static_topos_poprep" topologies to the topology database, in which
	  the topology ID will be validated.
   */
   result = topo_db_add_internal_topologies(DYNA_SVC_PP_TYPE_POPREP, SIZE_OF_ARRAY(audproc_custom_static_topos_poprep), audproc_custom_static_topos_poprep);
   if (ADSP_FAILED(result))
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Failed to add Custom POPREP topologies with %d", result);
      return result;
   }

   /* Adding custom static toplogy of type COPP to the topology database.
      Here "topo_db_add_internal_topologies()" API is used to add "audproc_custom_static_topos_copp" topologies to the topology database, in which
	  the topology ID will be validated.
   */
   result = topo_db_add_internal_topologies(DYNA_SVC_PP_TYPE_COPP, SIZE_OF_ARRAY(audproc_custom_static_topos_copp), audproc_custom_static_topos_copp);
   if (ADSP_FAILED(result))
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Failed to add Custom COPP topologies with %d", result);
      return result;
   }

   /* Adding custom static toplogy of type COPREP to the topology database 
      Here "topo_db_add_internal_topologies()" API is used to add "audproc_custom_static_topos_coprep" topologies to the topology database, in which
	  the topology ID will be validated.
   */
   result = topo_db_add_internal_topologies(DYNA_SVC_PP_TYPE_COPREP, SIZE_OF_ARRAY(audproc_custom_static_topos_coprep), audproc_custom_static_topos_coprep);
   if (ADSP_FAILED(result))
   {
      MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Failed to add Custom COPREP topologies with %d", result);
      return result;
   }

   /* Adding custom modules to the AMDB.
      Here it will add all the modules that are added to "audproc_custom_module_definitions" table.
   */
   for (uint32_t i = 0; i < SIZE_OF_ARRAY(audproc_custom_module_definitions); i++)
   {
      ADSPResult errCode = adsp_amdb_add_static_appi(audproc_custom_module_definitions[i].module_id,
            audproc_custom_module_definitions[i].getsize_f,
            audproc_custom_module_definitions[i].init_f);
      if(ADSP_FAILED(errCode))
      {
         MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "Failed to add custom static module %lu", audproc_custom_module_definitions[i].module_id);
      }
   }

   return result;
}

/* =================================================================================================
 * Function Name :  hap_topo_init_get_custom_KCPS
 *
 * Purpose		 :	To return custom static module KCPS value.
 *
 * Description	 :  This function will receive the custom static module ID as an input argument and 
 *					returns the custom static module ID KCPS value.
 *					Customer need to add module ID and its KCPS value to the KCPS_info[] lookup table.
 *
 * Input		 :	module_id	-> Module ID of the audio PP module
 *
 * Output		 :  KCPS of audio PP module, if module is available
 *					0, if module is not available
 *
 * ================================================================================================*/
uint32_t hap_topo_init_get_custom_KCPS(const uint32_t module_id)
{
   /* Search the custom static module ID in the KCPS lookup table and return its module KCPS value
      Here it will search the entire lookup table until it find the MODULE ID and then return its KCPS value.
   */
   for (uint32_t i = 0; i < SIZE_OF_ARRAY(Custom_KCPS_info); i++)
   {
      if (module_id == Custom_KCPS_info[i].module_id)
      {
         return Custom_KCPS_info[i].KCPS;
      }
   }

   /* If MODULE ID is not present in the KCPS lookup table then this function will return 'zero' */
   return 0;
}