/*========================================================================
qurt_elite_diag.cpp

This file contains a utility for dumping the contents of a buffer
on the diag in hex form.

Copyright (c) 2010 Qualcomm Technologies, Incorporated.  All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
*//*====================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/elite/qurt_elite/src/qurt_elite_diag.cpp#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
10/18/10   dg      Created file.

========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */
#include "qurt_elite.h"

/*--------------------------------------------------------------*/
/* Macro definitions                                            */
/* -------------------------------------------------------------*/

/* -----------------------------------------------------------------------
** Constant / Define Declarations
** ----------------------------------------------------------------------- */

/* =======================================================================
**                          Function Definitions
** ======================================================================= */

void qurt_elite_hexdump(const uint8_t* buffer, int32_t size)
{
   // output name and size
   MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "buffer addr: 0x%lx len: %ld", (uint32_t)buffer, size);

   // print 8 bytes per line
   for (int i =0; i + 8 <= size; i += 8 ) {
      MSG_8(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "%02hX %02hX %02hX %02hX %02hX %02hX %02hX %02hX",
            buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
      buffer += 8;
   }
}

