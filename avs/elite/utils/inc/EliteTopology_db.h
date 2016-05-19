/*========================================================================*/
/**
@file EliteTopology_db.h
@brief This file declares the interface for the Common topology database.

This file has the interface for the Common topology database module. This module
allows storage and query of Common topologies.

*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      Elite_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*========================================================================
Copyright (c) 2012, 2014 Qualcomm Technologies, Inc. All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
Export of this technology or software is regulated by the U.S. Government,
Diversion contrary to U.S. law prohibited.
========================================================================== */

/*========================================================================
Edit History

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/11/14   sw      (Tech Pubs) Added Doxygen markup/comments for 2.6.
07/25/12   Unni    Added lsm_add_static_topologies_and_modules
03/27/12   DG      Created file.
========================================================================== */
#ifndef ELITE_TOPOLOGY_DB_H
#define ELITE_TOPOLOGY_DB_H

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include "qurt_elite.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/*----------------------------------------------------------------------------
 * Type Declarations
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Class Definitions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 *--------------------------------------------------------------------------*/

/** @ingroup elite_topodb_init_db
  Initializes the global topology and module databases used by the Elite
  services.
  
  This function internally calls the following functions to populate the
  databases with statically defined modules and topologies:
  - afe_add_static_topologies_and_modules()
  - AudPP_AddStaticTopologiesAndModules()
  - lsm_add_static_topologies_and_modules() 

  @return
  ADSP_EOK -- Success.
  @par
  Error code -- None of the databases have been initialized.

  @dependencies
  None.
*/
ADSPResult Elite_InitializeDataBases(void);

/** @ingroup elite_topodb_deinit_db
  Deinitializes the global topology and module databases. 

  @return
  None.

  @dependencies
  Elite_InitializeDataBases() must have been called, and it must have returned
  ADSP_EOK.
*/
void Elite_DeinitializeDataBases(void);

ADSPResult Elite_ResetTopologyDatabase(void);

ADSPResult afe_add_static_topologies(void);

/** @ingroup elite_topodb_afe_add_st_topo
  Adds static the topologies and modules required by the AFE service to the
  global databases.

  @return
  ADSP_EOK -- All topologies and modules were added successfully.
  @par
  Error code -- Topology or module addition failed. Any topologies and modules
  that were added successfully are still usable.

  @dependencies
  The global databases must have been initialized using
  Elite_InitializeDataBases().
*/
ADSPResult afe_add_static_topologies_and_modules(void);

ADSPResult AudPP_AddStaticTopologies(void);

/** @ingroup elite_topodb_app_add_st_topo
  Adds static the topologies and modules required by the audio
  pre/postprocessor services to the global databases.

  @return
  ADSP_EOK -- All topologies and modules were added successfully.
  @par
  Error code -- Topology or module addition failed. Any topologies and modules
  that were added successfully are still usable.

  @dependencies
  The global databases must have been initialized using
  Elite_InitializeDataBases().
*/
ADSPResult AudPP_AddStaticTopologiesAndModules(void);

/** @ingroup elite_topodb_lsm_add_st_topo
  Adds static the topologies and modules required by the LSM service to the
  global databases.

  @return
  ADSP_EOK -- All topologies and modules were added successfully.
  @par
  Error code -- Topology or module addition failed. Any topologies and modules
  that were added successfully are still usable.

  @dependencies
  The global databases must have been initialized using
  Elite_InitializeDataBases().
*/
ADSPResult lsm_add_static_topologies(void);

ADSPResult lsm_add_static_topologies_and_modules(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // #ifndef ELITE_TOPOLOGY_DB_H


