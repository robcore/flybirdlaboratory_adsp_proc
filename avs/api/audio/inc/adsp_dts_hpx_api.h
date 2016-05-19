/*===========================================================================
  Copyright (c) 2013-2014 Qualcomm Technologies, Inc. All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.
  =========================================================================== */
#ifndef ADSP_DTS_HPX_API_H
#define ADSP_DTS_HPX_API_H

/**
   @file adsp_dts_hpx_api.h

   @brief This file contains the api definitions for dts headphone X
   premix and postmix modules
*/

/*===========================================================================
Edit History
when         who       what, where, why
----------   ---       ------------------------------------------------------
2013/10/22   kgodara   DTS eagle module and static topo ids

============================================================================= */

#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/


/** DTS postmix COPP Topology ID. The client can route multiple ASM sessions
    to this COPP with Matrix operating in Native mode.
*/
#define ADM_CMD_COPP_OPEN_TOPOLOGY_ID_DTS_HPX                                               0X00010347


/**
 * DTS postmix module id. Configuration of DTS postmix module must be done
 * by dts configurator and workspace test tool and should not be attempted
 * by anything else.
*/
#define AUDPROC_MODULE_ID_DTS_HPX_POSTMIX                                                   0X0001077B


/** DTS premix popp topology id. This topology id can be used to open popp for
    premix module of dts headphone X.
    This topology has following modules in it
     - Resampler                   (#AUDPROC_MODULE_ID_RESAMPLER)
     - DTS_HPX_premix              (#AUDPROC_MODULE_ID_DTS_HPX_PREMIX)
*/
#define ASM_STREAM_POSTPROC_TOPO_ID_DTS_HPX_PREMIX                                          0X00010DED


/**
 * DTS premix module id. Configuration of DTS premix module must be done
 * by dts configurator and workspace test tool and should not be attempted
 * by anything else.
*/
#define AUDPROC_MODULE_ID_DTS_HPX_PREMIX                                                    0X0001077C



/**
 * Library Description strings for DTS HPX library used by DTS Eagle
 * Driver to show description of current eagle library in ADSP. This
 * api will be called by ADSP Core services.
 */
#define AUDPROC_PARAM_ID_DTSHPX_DTS_PARAM_LIBRARY_DESCRIPTION_STRING                        0X1001514C

/**
 * Library version strings for DTS HPX library used by DTS Eagle
 * Driver to show version number of current eagle library in ADSP. This
 * api will be called by ADSP Core services.
 */
#define AUDPROC_PARAM_ID_DTSHPX_DTS_PARAM_LIBRARY_VERSION_STRING                            0X1001514D

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* ADSP_DTS_HPX_API_H */

