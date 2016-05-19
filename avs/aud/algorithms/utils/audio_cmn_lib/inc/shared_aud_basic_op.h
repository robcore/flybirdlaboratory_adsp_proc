#ifndef __SHARED_AUDIO_BASIC_OP_EXT_H_
#define __SHARED_AUDIO_BASIC_OP_EXT_H_
/*========================================================================

B A S I C   O P   E X T

*/

/**
@file audio_basic_op_ext.h

basic_op_ext is an extension of basic_op.h, with additional intrinsics
used by linking code.
*/

/*===========================================================================
NOTE: The @brief description and any detailed descriptions above do not appear 
      in the PDF. 

      The elite_audio_mainpage.dox file contains all file/group descriptions 
      that are in the output PDF generated using Doxygen and Latex. To edit or 
      update any of the file/group text in the PDF, edit the 
      elite_audio_mainpage.dox file or contact Tech Pubs.
===========================================================================*/

/*========================================================================
Copyright (c) 2008, 2010 Qualcomm Technologies, Incorporated.  All rights reserved.
Qualcomm Proprietary.  Export of this technology or software is regulated
by the U.S. Government, Diversion contrary to U.S. law prohibited.
====================================================================== */

/*========================================================================
Edit History

when       who     what, where, why
--------   ---     -------------------------------------------------------
04/22/08   mc      Created file.
10/20/10   sw,kli  (Tech Pubs) Edited/added Doxygen comments and markup.
========================================================================== */


/* =======================================================================
INCLUDE FILES FOR MODULE
========================================================================== */


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/** @addtogroup math_operations
@{ */

/* -----------------------------------------------------------------------
** Macro Definitions
** ----------------------------------------------------------------------- */


/** QFormat of 32-bit PCM rendered or forwarded by audio codec
*/
#define PCM_32BIT_Q_FORMAT              31  /* Q31 */

/** QFormat of 16-bit PCM rendered or forwarded by audio codec
*/
#define PCM_16BIT_Q_FORMAT              15  /* Q15 */

/** QFormat of 32-bit PCM internal to Elite frame work
*/
#define ELITE_32BIT_PCM_Q_FORMAT        27  /* Q27 */

/** Shift factor for Q31 <=> Q28 conversion for 32-bit PCM
*/
#define QFORMAT_SHIFT_FACTOR            (PCM_32BIT_Q_FORMAT - ELITE_32BIT_PCM_Q_FORMAT)

/** Shift factor for Q28 <=> Q15 conversion
*/
#define BYTE_UPDOWN_CONV_SHIFT_FACT     (ELITE_32BIT_PCM_Q_FORMAT - PCM_16BIT_Q_FORMAT) // (Q28 - Q15)


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /*__BASIC_OP_EXT_H_*/
