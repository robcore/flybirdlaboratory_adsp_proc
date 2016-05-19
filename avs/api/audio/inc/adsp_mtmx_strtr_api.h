/*========================================================================*/
/**
@file adsp_mtmx_strtr_api.h

This file contains the structure definitions for Audio Rx/Tx Matrix and
Rx/Tx Stream Router Module IDs, Parameter IDs.
*/
/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      The description that displays in the PDF is located in the
      audio_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/
/*===========================================================================
Copyright (c) 2012-2013 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
======================================================================== */
/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_mtmx_strtr_api.h#3 $

when         who     what, where, why
--------     ---     -------------------------------------------------------
09/10/14     sw      (Tech Pubs) Merged Doxygen comments from 2.4.
09/06/13     sw      (Tech Pubs) Merged Doxygen comments/markup from 2.0.
08/06/12     sw      (Tech Pubs) Edited comments and Doxygen markup.
08/02/2012   rb      created
========================================================================== */

#ifndef _ADSP_MTMX_STRRTR_API_H_
#define _ADSP_MTMX_STRRTR_API_H_

#include "mmdefs.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/** @addtogroup asmsess_module_av_sync
@{ */
/** Module used for AV synchronization-related parameters used in the matrix
    mixer and stream router.

    @par Rx Set Command Parameters
    For the #ASM_SESSION_CMD_SET_MTMX_STRTR_PARAMS_V2 command on the Rx path,
    the following parameter IDs are supported:
    - #ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_START_V2
    - #ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_END_V2
    - #ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_START_V2
    - #ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_END_V2
       
    @par Rx Get Command Parameters
    For the #ASM_SESSION_CMD_GET_MTMX_STRTR_PARAMS_V2 command on the Rx path,
    the following parameter IDs are supported:
    - #ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_V2
    - #ASM_SESSION_MTMX_STRTR_PARAM_SESSION_INST_STATISTICS_V2
    - #ASM_SESSION_MTMX_STRTR_PARAM_SESSION_CUMU_STATISTICS_V2
*/
#define ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC                        0x00010DC6

/* Generic structure payload for:
 * ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_START_V2
 * ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_END_V2
 * ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_START_V2
 * ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_END_V2 */
typedef struct asm_session_mtmx_strtr_param_window_v2_t asm_session_mtmx_strtr_param_window_v2_t;

#include "adsp_begin_pack.h"

/** Generic payload of the window parameters in the
    #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC module.

    @note1hang This payload is supported only for a Set command (not a Get
               command) on the Rx path.
*/
struct asm_session_mtmx_strtr_param_window_v2_t
{
    uint32_t                  window_lsw;
    /**< Lower 32 bits of the render window start value. */

    uint32_t                  window_msw;
    /**< Upper 32 bits of the render window start value.

         The 64-bit number formed by window_lsw and window_msw specifies a
         signed 64-bit window value in microseconds. The sign extension is
         necessary.
         
         This value is used by the following parameter IDs:
         - #ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_START_V2
         - #ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_END_V2
         - #ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_START_V2
         - #ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_END_V2

         The value depends on which parameter ID is used.

         The aDSP honors the windows at a granularity of 1 ms. */
}
#include "adsp_end_pack.h"
;

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to specify the
    render window start value.
    This parameter is supported only for a Set command (not a Get command) in
    the Rx direction (#ASM_SESSION_CMD_SET_MTMX_STRTR_PARAMS_V2).

    Render window start is a value (session time minus timestamp, or ST-TS)
    below which frames are held, and after which frames are immediately
    rendered.

    @msgpayload
    For the payload format, see asm_session_mtmx_strtr_param_window_v2_t.
    @par
    @values The signed 64 bit number formed by window_lsw and window_msw must
    be less than or equal to zero. @newpage
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_START_V2            0x00010DD1

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to specify the
    render window end value.
    This parameter is supported only for a Set command (not a Get command) in
    the Rx direction (#ASM_SESSION_CMD_SET_MTMX_STRTR_PARAMS_V2).

    Render window end is a value (session time minus timestamp) above which
    frames are dropped, and below which frames are immediately rendered.

    @msgpayload
    For the payload format, see asm_session_mtmx_strtr_param_window_v2_t.
    @par
    @values The signed 64 bit number formed by window_lsw and window_msw must
    be greater than or equal to zero.
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_RENDER_WINDOW_END_V2              0x00010DD2

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to specify the
    statistics window start value.
    This parameter is supported only for a Set command (not a Get command) in
    the Rx direction (#ASM_SESSION_CMD_SET_MTMX_STRTR_PARAMS_V2).

    Statistics window start is a value (session time minus timestamp) below
    which frames are considered early when calculating statistics, and above
    which frames are considered on time.

    @msgpayload
    For the payload format, see asm_session_mtmx_strtr_param_window_v2_t.
    @par
    @values The signed 64 bit number formed by window_lsw and window_msw must
    be less than or equal to zero.
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_START_V2             0x00010DD3

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to
    specify the statistics window end value.
    This parameter is supported only for a Set command (not a Get command) in
    the Rx direction (#ASM_SESSION_CMD_SET_MTMX_STRTR_PARAMS_V2).

    Statistics window end is a value (session time minus timestamp) above
    which frames are considered late when calculating statistics, and below
    which frames are considered on time.

    @msgpayload
    For the payload format, see asm_session_mtmx_strtr_param_window_v2_t.
    @par
    @values The signed 64 bit number formed by window_lsw and window_msw must
    be greater than or equal to zero. @newpage
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_STAT_WINDOW_END_V2              0x00010DD4


/***********************************************************************************************************/

/* This command replaces previous ASM_SESSION_CMD_GET_SESSION_TIME (and its versions). */

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to get the
    session time.
    This parameter is supported only for a Get command (not a Set command) on
    the Rx path (#ASM_SESSION_CMD_GET_MTMX_STRTR_PARAMS_V2).

    The session time value must be interpreted by clients as a signed 64-bit
    value. A negative session time can be returned in cases where the client
    wants to start running a session in the future, but first queries for the
    session clock.

    The absolute time value in the command response must be interpreted by
    clients as an unsigned 64-bit value. The absolute time can be in the past
    or future.

    @msgpayload{asm_session_mtmx_strtr_param_session_time_v2_t}
    @table{weak__asm__session__mtmx__strtr__param__session__time__v2__t}
    @newpage
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_V2              0x00010DD5

/* Structure for query of session time. */
typedef struct asm_session_mtmx_strtr_param_session_time_v2_t asm_session_mtmx_strtr_param_session_time_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_session_mtmx_strtr_param_session_time_v2_t
@{ */
/* Payload of the ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_V2 parameter.
*/
struct asm_session_mtmx_strtr_param_session_time_v2_t
{
    uint32_t                  session_time_lsw;
    /**< Lower 32 bits of the current session time in microseconds. */

    uint32_t                  session_time_msw;
    /**< Upper 32 bits of the current session time in microseconds.

         The 64-bit number formed by session_time_lsw and session_time_msw
         is treated as signed. */

    uint32_t                  absolute_time_lsw;
    /**< Lower 32 bits of the 64-bit absolute time in microseconds.
    
         This is the time when the sample corresponding to the session_time_lsw
         is rendered to the hardware. This absolute time can be slightly in the
         future or past. */

    uint32_t                  absolute_time_msw;
    /**< Upper 32 bits of the 64-bit absolute time in microseconds.
    
         This is the time when the sample corresponding to the session_time_msw
         is rendered to hardware. This absolute time can be slightly in the
         future or past.

         The 64-bit number formed by absolute_time_lsw and absolute_time_msw
         is treated as unsigned. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_session_mtmx_strtr_param_session_time_v2_t */
/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to get the
    session time.
    This parameter is supported only for a Get command (not a Set command) on
    the Rx path (#ASM_SESSION_CMD_GET_MTMX_STRTR_PARAMS_V2).

    This parameter differs from #ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_V2
    in that it supports a timestamp and additional flags.

    The session time value must be interpreted by clients as a signed 64-bit
    value. A negative session time can be returned in cases where the client
    wants to start running a session in the future, but first queries for the
    session clock.

    The absolute time value in the command response must be interpreted by
    clients as an unsigned 64-bit value. The absolute time can be in the past
    or future.

    The timestamp field is populated using the last processed timestamp.
    This field follows certain rules:
    - For an uninitialized or invalid timestamp, the value reads zero, and the
      flag that follows this timestamp field is set to zero to indicate
      Uninitialized/Invalid.
    - During steady state rendering, it reflects the last processed timestamp.

    The timestamp value in the command response must be interpreted by
    clients as an unsigned 64-bit value.

    @msgpayload{asm_session_mtmx_strtr_param_session_time_v3_t}
    @table{weak__asm__session__mtmx__strtr__param__session__time__v3__t}
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_V3              0x00012F0B

/** Bitmask for the Timestamp Valid flag. */
#define ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_TIMESTAMP_VALID_FLAG_BIT_MASK    (0x80000000UL)

/** Shift value for the Timestamp Valid flag. */
#define ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_TIMESTAMP_VALID_FLAG_BIT_SHIFT                          31
/* Structure for query of session time v2_1. */
typedef struct asm_session_mtmx_strtr_param_session_time_v3_t asm_session_mtmx_strtr_param_session_time_v3_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_session_mtmx_strtr_param_session_time_v3_t
@{ */
/* Payload of the ASM_SESSION_MTMX_STRTR_PARAM_SESSION_TIME_V3
    parameter.
*/
struct asm_session_mtmx_strtr_param_session_time_v3_t
{
    uint32_t                  session_time_lsw;
    /**< Lower 32 bits of the current session time in microseconds. */

    uint32_t                  session_time_msw;
    /**< Upper 32 bits of the current session time in microseconds.

         The 64-bit number formed by session_time_lsw and session_time_msw
         is treated as signed. */

    uint32_t                  absolute_time_lsw;
    /**< Lower 32 bits of the 64-bit absolute time in microseconds.

         This is the time when the sample corresponding to the session_time_lsw
         is rendered to the hardware. This absolute time can be slightly in the
         future or past. */

    uint32_t                  absolute_time_msw;
    /**< Upper 32 bits of the 64-bit absolute time in microseconds.

         This is the time when the sample corresponding to the session_time_msw
         is rendered to hardware. This absolute time can be slightly in the
         future or past.

         The 64-bit number formed by absolute_time_lsw and absolute_time_msw
         is treated as unsigned. */

    uint32_t                  time_stamp_lsw;
    /**< Lower 32 bits of the last processed timestamp in microseconds. */

    uint32_t                  time_stamp_msw;
    /**< Upper 32 bits of the last processed timestamp in microseconds.

         The 64-bit number formed by time_stamp_lsw and time_stamp_lsw
         is treated as unsigned. */

    uint32_t                  flags;
    /**< Keeps track of any additional flags needed.

         @values{for bit 31}
         - 0 -- Uninitialized/invalid
         - 1 -- Valid

         All other bits are reserved; clients must set them to zero. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_session_mtmx_strtr_param_session_time_v3_t */

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to specify the
    instantaneous statistics of the session.
    This parameter is supported only for a Get command (not a Set command) on
    the Rx path (#ASM_SESSION_CMD_GET_MTMX_STRTR_PARAMS_V2).

    The observation period is defined as the period between any change in the
    render or statistics windows.

    Unless start and end of the statistics window are set, statistics cannot be
    queried (the query command fails).

    @msgpayload{asm_session_mtmx_strtr_session_inst_statistics_v2_t}
    Figure @xref{fig:RegionsStTsPlayback} illustrates the definition of regions
    A, B, and C.
    @tablens{weak__asm__session__mtmx__strtr__session__inst__statistics__v2__t}
    @newpage
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_SESSION_INST_STATISTICS_V2        0x00010DD6

/* Structure query of instantaneous statistics */
typedef struct asm_session_mtmx_strtr_session_inst_statistics_v2_t asm_session_mtmx_strtr_session_inst_statistics_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_session_mtmx_strtr_session_inst_statistics_v2_t
@{ */
/* Payload of the ASM_SESSION_MTMX_STRTR_PARAM_SESSION_INST_STATISTICS_V2
    parameter.
*/
struct asm_session_mtmx_strtr_session_inst_statistics_v2_t
{
    uint32_t                  absolute_time_lsw;
    /**< Lower 32 bits of the absolute time in microseconds when
         instantaneous statistics are calculated. */

    uint32_t                  absolute_time_msw;
    /**< Upper 32 bits of the absolute time in microseconds when
         instantaneous statistics are calculated.

         The 64-bit number formed by absolute_time_lsw and absolute_time_msw
         is treated as unsigned. */

    uint32_t                  duration_region_A_lsw;
    /**< Instantaneous statistics: lower 32 bits of the duration of frames in
         region A. */

    uint32_t                  duration_region_A_msw;
    /**< Instantaneous statistics: upper 32 bits of the duration of frames in
         region A.

         The 64-bit number formed by duration_region_A_lsw and
         duration_region_A_msw is a unsigned value in microseconds.
         This value is the duration of frames in region A during the specified
         observation period. */

    uint32_t                  average_region_A_lsw;
    /**< Instantaneous statistics: lower 32 bits of the average of frames in
         region A. */

    uint32_t                  average_region_A_msw;
    /**< Instantaneous statistics: upper 32 bits of the average of frames in
         region A.

         The 64-bit number formed by average_region_A_lsw and
         average_region_A_msw is a signed average value (session time minus
         timestamp) in microseconds. This value is the average of frames in
         region A during the specified observation period. */

    uint32_t                  duration_region_B_lsw;
    /**< Instantaneous statistics: lower 32 bits of the duration of frames in
         region B. */

    uint32_t                  duration_region_B_msw;
    /**< Instantaneous statistics: upper 32 bits of the duration of frames in
         region B.

         The 64-bit number formed by duration_region_B_lsw and
         duration_region_B_msw is a unsigned value in microseconds.
         This value is the duration of frames in region B during the specified
         observation period. */

    uint32_t                  average_region_B_lsw;
    /**< Instantaneous statistics: lower 32 bits of the average of frames in
         region B. */

    uint32_t                  average_region_B_msw;
    /**< Instantaneous statistics: upper 32 bits of the average of frames in
         region B.

         The 64-bit number formed by average_region_B_lsw and
         average_region_B_msw is a signed average value (session time minus
         timestamp) in microseconds. This value is the average of frames in
         region B during the specified observation period. */

    uint32_t                  duration_region_C_lsw;
    /**< Instantaneous statistics: lower 32 bits of the duration of frames in
         region C. */

    uint32_t                  duration_region_C_msw;
    /**< Instantaneous statistics: upper 32 bits of the duration of frames in
         region C.

         The 64-bit number formed by duration_region_C_lsw and
         duration_region_C_msw is a unsigned value in microseconds.
         This value is the duration of frames in region C during the specified
         observation period. */

    uint32_t                  average_region_C_lsw;
    /**< Instantaneous statistics: lower 32 bits of the average of frames in
         region C. */

    uint32_t                  average_region_C_msw;
    /**< Instantaneous statistics: upper 32 bits of the average of frames in
         region C.

         The 64-bit number formed by average_region_C_lsw and
         average_region_C_msw is a signed average value (session time minus
         timestamp) in microseconds. This value is the average of frames in
         region C during the specified observation period. */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_session_mtmx_strtr_session_inst_statistics_v2_t */

/** Parameter used by #ASM_SESSION_MTMX_STRTR_MODULE_ID_AVSYNC to specify the
    cumulative statistics of the session.
    This parameter is supported only for a Get command (not a Set command) on
    the Rx path (#ASM_SESSION_CMD_GET_MTMX_STRTR_PARAMS_V2).

    The observation period is defined as the lifetime of a session.

    Unless statistics window start and end are set, statistics cannot be
    queried (the query command will fail).

    @msgpayload{asm_session_mtmx_strtr_session_cumu_statistics_v2_t}
    Figure @xref{fig:RegionsStTsPlayback} illustrates the definition of regions
    A, B, and C.
    @tablens{weak__asm__session__mtmx__strtr__session__cumu__statistics__v2__t}
*/
#define ASM_SESSION_MTMX_STRTR_PARAM_SESSION_CUMU_STATISTICS_V2        0x00010DD7

/* Structure query of cumulative statistics */
typedef struct asm_session_mtmx_strtr_session_cumu_statistics_v2_t asm_session_mtmx_strtr_session_cumu_statistics_v2_t;

#include "adsp_begin_pack.h"

/** @weakgroup weak_asm_session_mtmx_strtr_session_cumu_statistics_v2_t
@{ */
/* Payload of the ASM_SESSION_MTMX_STRTR_PARAM_SESSION_CUMU_STATISTICS_V2
    parameter.
*/
struct asm_session_mtmx_strtr_session_cumu_statistics_v2_t
{
    uint32_t                  absolute_time_lsw;
    /**< Lower 32 bits of the absolute time in microseconds when
         cumulative statistics are calculated. */

    uint32_t                  absolute_time_msw;
    /**< Upper 32 bits of the absolute time in microseconds when
         cumulative statistics are calculated.

         The 64-bit number formed by absolute_time_lsw and absolute_time_msw
         is treated as unsigned. */

    uint32_t                  duration_region_A_lsw;
    /**< Cumulative statistics: lower 32 bits of the duration of frames in
         region A. */

    uint32_t                  duration_region_A_msw;
    /**< Cumulative statistics: upper 32 bits of the duration of frames in
         region A.

         The 64-bit number formed by duration_region_A_lsw and
         duration_region_A_msw is a unsigned value in microseconds.
         This value is the duration of frames in region A during the specified
         observation period. */

    uint32_t                  average_region_A_lsw;
    /**< Cumulative statistics: lower 32 bits of the average of frames in
         region A. */

    uint32_t                  average_region_A_msw;
    /**< Cumulative statistics: upper 32 bits of the average of frames in
         region A.

         The 64-bit number formed by average_region_A_lsw and
         average_region_A_msw is a signed average value (session time minus
         timestamp) in microseconds. This value is the average of frames in
         region A during the specified observation period. */

    uint32_t                  duration_region_B_lsw;
    /**< Cumulative statistics: lower 32 bits of the duration of frames in
         region B. */

    uint32_t                  duration_region_B_msw;
    /**< Cumulative statistics: upper 32 bits of the duration of frames in
         region B.

         The 64-bit number formed by duration_region_B_lsw and
         duration_region_B_msw is a unsigned value in microseconds.
         This value is the duration of frames in region B during the specified
         observation period. */

    uint32_t                  average_region_B_lsw;
    /**< Cumulative statistics: lower 32 bits of the average of frames in
         region B. */

    uint32_t                  average_region_B_msw;
    /**< Cumulative statistics: upper 32 bits of the average of frames in
         region B.

         The 64-bit number formed by average_region_B_lsw and
         average_region_B_msw is a signed average value (session time minus
         timestamp) in microseconds. This value is the average of frames in
         region B during the specified observation period. */

    uint32_t                  duration_region_C_lsw;
    /**< Cumulative statistics: lower 32 bits of the duration of frames in
         region C. */

    uint32_t                  duration_region_C_msw;
    /**< Cumulative statistics: upper 32 bits of the duration of frames in
         region C.

         The 64-bit number formed by duration_region_C_lsw and
         duration_region_C_msw is a unsigned value in microseconds.
         This value is the duration of frames in region C during the specified
         observation period. */

    uint32_t                  average_region_C_lsw;
    /**< Cumulative statistics: lower 32 bits of the average of frames in
         region C. */

    uint32_t                  average_region_C_msw;
    /**< Cumulative statistics: upper 32 bits of the average of frames in
         region C.

         The 64-bit number formed by average_region_C_lsw and
         average_region_C_msw is a signed average value (session time minus
         timestamp) in microseconds. This value is the average of frames in
         region C during the specified observation period. @newpagetable */
}
#include "adsp_end_pack.h"
;
/** @} */ /* end_weakgroup weak_asm_session_mtmx_strtr_session_cumu_statistics_v2_t */
/** @} */ /* end_addtogroup asmsess_module_av_sync */

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /* _ADSP_MTMX_STRRTR_API_H_ */
