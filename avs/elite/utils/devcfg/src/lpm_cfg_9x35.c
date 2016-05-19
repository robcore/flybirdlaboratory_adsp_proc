/*========================================================================

*//** @file lpm_cfg_9x35.h
This file contains LPM configuration for MDM9x35

Copyright (c) 2013 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: 

when       who     what, where, why
--------   ---     -------------------------------------------------------
07/29/13   aprasad Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "lpm_prop.h"

/* LPM configuration for MDM9x35 */
const lpm_prop_struct_t lpm_prop = {0xFE100000, 16*1024, 0, 5*1024, 11*1024, 0, 0};