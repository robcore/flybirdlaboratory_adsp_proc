#ifndef SNS_UIMG_UTILS_H
#define SNS_UIMG_UTILS_H
/*============================================================================
  @file sns_uimg_utils.h

  @brief
  Contains definitions of utilities to make writing uImage aware code easier.

  <br><br>

  Copyright (c) 2014 QUALCOMM Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
  ============================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order. Please
  use ISO format for dates.

  $Header: //components/rel/ssc.adsp/2.6.1/common/inc/sns_uimg_utils.h#1 $
  $DateTime: 2014/12/01 08:57:58 $

  when       who    what, where, why
  ---------- --- -----------------------------------------------------------
  2014-08-15 asj Initial version
  ============================================================================*/


/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/

/* We only support the following modules */
typedef enum 
{
  SNS_UIMG_MEMGR,
  SNS_UIMG_SMR,
  SNS_UIMG_SMR_MAX_CLIENTS
}sns_uimg_module_e;

/*=========================================================================
  FUNCTION:  sns_utils_place_uimge_hold
  =======================================================================*/
/*!
    @brief Exits uImage if needed, and places a hold on the system's entry
           into uImage. This restriction stays in effect until the hold is
           removed for the calling module.

    @param[i] module: Module placing the hold
*/
/*=======================================================================*/
void sns_utils_place_uimge_hold(sns_uimg_module_e module);

/*=========================================================================
  FUNCTION:  sns_utils_remove_uimge_hold
  =======================================================================*/
/*!
    @brief Removes any hold on uImage entry placed by a module.
           If all modules have removed their holds, UTILS shall vote for
           uimge entry with the sensors PM module.

    @param[i] module: Module placing the hold
*/
/*=======================================================================*/
void sns_utils_remove_uimage_hold(sns_uimg_module_e module);

/*=========================================================================
  FUNCTION:  sns_utils_remove_uimge_hold
  =======================================================================*/
/*!
    @brief Initializes the utils module.
*/
/*=======================================================================*/
void sns_uimg_utils_init(void);

#endif /* SNS_UIMG_UTILS_H*/
