/*========================================================================

*//** @file lpm_cfg_8932.h
This file contains LPM configuration for MSM8932

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

/* LPM configuration for MSM8932 */
const lpm_prop_struct_t lpm_prop = {0xFE090000, 64*1024, 48*1024, 16*1024, 0, 0, 172*1024};