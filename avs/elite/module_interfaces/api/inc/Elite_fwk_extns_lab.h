#ifndef ELITE_FWK_EXTNS_LAB_H
#define ELITE_FWK_EXTNS_LAB_H

/**
  @file Elite_fwk_extns_lab.h

  @brief Parameters required to be implemented for Look Ahead Buffering(LAB)

  This file defines a framework extensions and corresponding private messages
  for Look Ahead Buffering(LAB).
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      Elite_CAPIv2_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*==============================================================================
  Copyright (c) 2012-2014 Qualcomm Technologies, Inc.(QTI)
  All rights reserved.
  Qualcomm Technologies Proprietary and Confidential.
==============================================================================*/

/*==============================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/api/inc/Elite_fwk_extns_lab.h#3 $

  when        who      what, where, why
  --------    ---      -------------------------------------------------------
  11/23/14    sw      (Tech Pubs) Edited Doxygen markup/comments for 2.6.
  08/05/14    SivaNaga   New
==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*------------------------------------------------------------------------------
 * Include Files
 *----------------------------------------------------------------------------*/
#include "Elite_CAPI_V2_types.h"

/** @addtogroup capiv2_ext_look_ahead_buf
@{ */

/** Unique identifier used to represent LAB framework extension for the Listen
    Stream Manager feature.

    This extension supports the PARAM_ID_KW_END_POSITION and
    PARAM_ID_KW_END_MAX_BUFFER_REQ parameters.
*/
#define FWK_EXTN_LAB 0x00012C11

/*------------------------------------------------------------------------------
 * Parameter definitions - Needs implementation in module/library
 *----------------------------------------------------------------------------*/
 
/** Parameter that indicates the keyword end position in samples from the end
    of the buffer for which detection happened.

    For example, in the Snapdragon@tm Voice Activation (SVA) solution, this
    parameter is used to omit the keyword before sending sending buffers to the
    HLOS. Other algorithms can use this extension in a similar way.

    @msgpayload{kw_end_position_t}
    @tablens{weak__kw__end__position__t} @newpage
*/
#define PARAM_ID_KW_END_POSITION   0x00012C12

/** @weakgroup weak_kw_end_position_t
@{ */
/** Data structure used when sending a keyword end position.
*/
typedef struct 
{
  uint32_t kw_end_position_samples;
  /**< Keyword end position in samples from the end of the buffer for which
       detection occurred. */
}kw_end_position_t;
/** @} */ /* end_weakgroup weak_kw_end_position_t */

/** Macro that sends a keyword end position maximum buffer size required to
    the framework.

    This parameter indicates the maximum delay between the keyword end
    position and the keyword detection in the stream. This delay is
    calculated in terms of samples starting from the frame for which a
    keyword is detected.

    @msgpayload{kw_end_max_delay_t}
    @tablens{weak__kw__end__max__delay__t}
*/
#define PARAM_ID_KW_END_MAX_BUFFER_REQ 0x00012C13

/** @weakgroup weak_kw_end_max_delay_t
@{ */
/** Data structure used when querying for the maximum number of samples that
    the Look Ahead Buffer needs to buffer.
*/
typedef struct
{
  uint32_t kw_end_max_delay_samples;
  /**< Maximum delay between the keyword end position and keyword detection in
       the stream.

       This delay is calculated in terms of samples starting from the frame for
       which a keyword is detected. */

}kw_end_max_delay_t;
/** @} */ /* end_weakgroup weak_kw_end_max_delay_t */

/** @} */ /* end_addtogroup capiv2_ext_look_ahead_buf */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* #ifndef ELITE_FWK_EXTNS_LAB_H*/
