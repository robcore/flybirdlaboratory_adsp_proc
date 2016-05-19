/*=============================================================================
  @file sns_smgr_pm_if_uimg.c

  This file contains interface between SMGR and PM.

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_pm_if_uimg.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-09-08  pn   Consolidated all PM interface functions
  2014-07-31  pn   Removed POWER_INTERFACE featurization
  2014-05-13  vy   Initial version , SMGR-PM interface

============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "sns_smgr_pm_if.h"
#include "sns_smgr_priv.h"

#if defined(SNS_USES_ISLAND)
#include "sns_rh_util.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"


/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_smgr_pm_stats_s smgr_pm_stats;

/*----------------------------------------------------------------------------
 *                             Local Functions
 * -------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
 *                             Public Functions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/*===========================================================================

  FUNCTION:   sns_smgr_get_curr_image_vote

===========================================================================*/
/*!
  @brief Returns the current image mode

  @param  none
  @return sns_pm_img_mode_e
 */
/*=========================================================================*/
sns_pm_img_mode_e sns_smgr_get_curr_image_vote(void)
{
  return smgr_pm_stats.img_mode;
}

/*===========================================================================

  FUNCTION:   sns_smgr_vote_image_mode

===========================================================================*/
/*!
  @brief Votes for the given mode if necessary

  @param  new_mode - the desired image mode
 
  @return none
 */
/*=========================================================================*/
void sns_smgr_vote_image_mode(sns_pm_img_mode_e new_mode)
{
  if ( smgr_pm_stats.img_mode != new_mode )
  {
    sns_pm_err_code_e  err;
    sns_pm_img_mode_e old_mode = smgr_pm_stats.img_mode;
    err = sns_pm_vote_img_mode(smgr_pm_stats.pm_client_handle, new_mode);
    if (err == SNS_PM_SUCCESS)
    {
      smgr_pm_stats.img_mode = new_mode;
    }
    SNS_SMGR_PM_IF_DBG3(HIGH, "image_vote - %u --> %u, result=%u", 
                     old_mode, smgr_pm_stats.img_mode, err);
  }
}


/*===========================================================================

  FUNCTION:   sns_smgr_enter_bigimage

===========================================================================*/
/*!
  @brief Enters bigimage mode

  @param  none
  @return none
 */
/*=========================================================================*/
void sns_smgr_enter_bigimage(void)
{
  sns_smgr_vote_image_mode(SNS_IMG_MODE_BIG);
}


/*===========================================================================

  FUNCTION:   sns_smgr_exit_bigimage

===========================================================================*/
/*!
  @brief Exits big image mode if safe to do so
  @param  none
  @return none
 */
/*=========================================================================*/
void sns_smgr_exit_bigimage(void)
{
  #define SNS_SMGR_U_EXIT_LO_THRESH_Q16 FX_FLTTOFIX_Q16(0.1)
  
  if ( smgr_pm_stats.img_mode == SNS_IMG_MODE_BIG 
       && !smgr_pm_stats.stay_in_bigimage )
  {
    if( sns_rh_get_report_count() > 0 
      && smgr_pm_stats.eff_wakeup_rate_hz_est > SNS_SMGR_U_EXIT_LO_THRESH_Q16 )
    {
      sns_smgr_vote_image_mode(SNS_IMG_MODE_MICRO);
    }
    else
    {
      sns_smgr_vote_image_mode(SNS_IMG_MODE_NOCLIENT);
    }
  }
}


#else /* NOT IN SNS_USES_ISLAND */

sns_pm_img_mode_e sns_smgr_get_curr_image_vote(void)
{
  return SNS_IMG_MODE_BIG;
}
void sns_smgr_vote_image_mode(sns_pm_img_mode_e new_mode){}
void sns_smgr_enter_bigimage( void ){}
void sns_smgr_exit_bigimage(void){}
void sns_smgr_set_stay_in_big_image(bool stay){}

#endif /* SNS_USES_ISLAND */

