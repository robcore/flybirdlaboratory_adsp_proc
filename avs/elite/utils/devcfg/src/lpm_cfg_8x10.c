/*========================================================================

*//** @file lpm_cfg_8x10.h
This file contains LPM configuration for MSM8x10

Copyright (c) 2012 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: 

when       who     what, where, why
--------   ---     -------------------------------------------------------
11/05/12   aprasad Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "lpm_prop.h"

/* LPM configuration for MSM8x10 */
/* LPA heap size is a multiple of 4KB so that it can be placed in OCMEM */
const lpm_prop_struct_t lpm_prop = {0xFE090000, 8*1024, 0, 8*1024, 0, 0, 172*1024};