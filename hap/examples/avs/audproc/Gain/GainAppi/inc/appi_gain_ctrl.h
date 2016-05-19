/* ======================================================================== */
/**
@file appi_gain_ctrl.h

   Header file to implement the Audio Post Processor Interface for 
   applying gain to input signal
*/

/* =========================================================================
  Copyright (c) 2010 QUALCOMM Technologies Incorporated.
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================== */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   11/04/10   ss      APPI wrapper
   ========================================================================= */

/*------------------------------------------------------------------------
 * Include files
 * -----------------------------------------------------------------------*/
#ifndef __APPI_GAIN_CTRL_H__
#define __APPI_GAIN_CTRL_H__

#include "Elite_APPI.h"
#include "gain_ctrl.h"

#ifdef __cplusplus
extern "C" {
#endif
/*------------------------------------------------------------------------
 * Macros, Defines, Type declarations
 * -----------------------------------------------------------------------*/
/*
 * Define Param IDs for Gain APPI module
 */
/** \brief Parameter ID of Gain example module for fixed point gain parameter */
#define PARAM_ID_GAIN_CTRL_MASTER_GAIN          0x10010081

/** \brief Parameter ID of Gain example module for floating point gain parameter */
#define PARAM_ID_GAIN_CTRL_MASTER_GAIN_FLOAT    0x10010082

/** \brief Structure for fixed point master gain parameter for volume control module */
typedef struct gain_ctrl_master_gain_t gain_ctrl_master_gain_t;

/** \brief Structure for fixed point master gain parameter for volume control module */
struct gain_ctrl_master_gain_t
{
    /** \brief Q13us Linear Gain */
    uint16_t                  master_gain;

    /** \brief Reserved field. Client must set this to zero */
    uint16_t                  reserved;
};

/** \brief Structure for floating point master gain parameter for volume control module */
typedef struct gain_ctrl_float_master_gain_t gain_ctrl_float_master_gain_t;

/** \brief Structure for floating point master gain parameter for volume control module */
struct gain_ctrl_float_master_gain_t
{
    /** \brief floating point gain in 32bits */
    float                  master_gain_float;
};

/*------------------------------------------------------------------------
 * Function declarations
 * -----------------------------------------------------------------------*/
ADSPResult appi_gain_ctrl_getsize(
      const appi_buf_t* params_ptr,
      uint32_t* size_ptr);

ADSPResult appi_gain_ctrl_init( 
      appi_t*              _pif,
      bool_t*              is_inplace_ptr,
      const appi_format_t* in_format_ptr,
      appi_format_t*       out_format_ptr,
      appi_buf_t*          info_ptr);

#ifdef __cplusplus
}
#endif

#endif //__APPI_GAIN_CTRL_H__
