/*========================================================================

*//** @file lpm_cfg_8084.c
This file contains LPM configuration for APQ8084

Copyright (c) 2013 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: 

when       who     what, where, why
--------   ---     -------------------------------------------------------
05/23/13   rr      Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "lpm_prop.h"

/* LPM configuration for APQ8084 */
const lpm_prop_struct_t lpm_prop = {0xFE100000, 64*1024, 48*1024, 16*1024, 0, 0, 172*1024};