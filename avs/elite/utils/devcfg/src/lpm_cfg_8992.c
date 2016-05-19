/*========================================================================

*//** @file lpm_cfg_8992.c
This file contains LPM configuration for MSM8992

Copyright (c) 2012 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: 

when       who     what, where, why
--------   ---     -------------------------------------------------------
10/16/14   jv      Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "lpm_prop.h"

/* LPM configuration for MSM8992 */
const lpm_prop_struct_t lpm_prop = {0xFE0E0000, 64*1024, 48*1024, 16*1024, 0, 0, 172*1024};
