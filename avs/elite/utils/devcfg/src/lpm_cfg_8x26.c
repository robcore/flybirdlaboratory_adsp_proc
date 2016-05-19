/*========================================================================

*//** @file lpm_cfg_8x26.h
This file contains LPM configuration for MSM8x26

Copyright (c) 2012 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: 

when       who     what, where, why
--------   ---     -------------------------------------------------------
09/14/12   rkc     Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "lpm_prop.h"

/* LPM configuration for MSM8x26 */
/* LPA heap sizes are a multiple of 4KB so that it can be placed in OCMEM */
const lpm_prop_struct_t lpm_prop = {0xFE090000, 64*1024, 52*1024, 12*1024, 0, 0, 172*1024};