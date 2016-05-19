/*=============================================================================
  @file sns_smgr_hw.c

  This file contains hw related features used by SMGR.

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_hw_uimg.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-10-02  jhh  Remove pnoc on/off for every sample
  2014-09-08  pn   Moved PM interface functions to PM_IF module
  2014-07-31  pn   Enabled power control; removed obsolete code
  2014-07-14  VY   Fixed compiler warnings
  2014-06-20  ps   Updates to turn on/off only bus instances used by Sensors
  2014-06-05  vy   Further refactored to support uImage  
  2014-05-29  ps   Fixed linux compilation errors 
  2014-05-29  pn   Fixed array access out-of-bound
  2014-05-09  sc   Added changes for uImage I2C driver integration
  2014-04-23  pn   Initial version
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "DDITlmm.h"

#include "sns_smgr_hw.h"
#include "sns_smgr_main.h"
#include "sns_smgr_util.h"

/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/
sns_hw_s   sns_smgr_hw;

/*===========================================================================

  FUNCTION:   sns_hw_set_qup_clk

===========================================================================*/
/*!
  @brief Enable/Disable i2c related clocks & gpio pins

  @detail

  @param[in] enable_flag:  enable/disable flag
  @return
   none
 */
/*=========================================================================*/
void sns_hw_set_qup_clk(bool enable_flag)
{
#if !defined(SNS_QDSP_SIM)
  uint8_t     i;
  int32 i2c_ret = I2C_RES_SUCCESS;
  I2cDrvCmdType   clock_cmd;

  if (sns_smgr_hw.i2c_clk.qupclk_on == enable_flag)
  {
    return;
  }

  if ( enable_flag )
  {
    clock_cmd = I2cDrvCmd_Vote_I2cClocsOn;
  }
  else
  { 
    clock_cmd = I2cDrvCmd_Vote_I2cClocsOff;
  }

  for ( i=0; i<sns_smgr_hw.i2c_bus_count && i2c_ret==I2C_RES_SUCCESS; i++ )
  {
    i2c_ret = I2cDrv_Open(sns_smgr_hw.i2c_bus_instances[i].i2c_bus_id, 
                          &(sns_smgr_hw.i2c_bus_instances[i].config), 
                          0);

    i2c_ret = ( (i2c_ret == I2C_RES_SUCCESS) && 
                 I2cDrv_Cmd ( &(sns_smgr_hw.i2c_bus_instances[i].config), 
                             clock_cmd, NULL) );

    if (I2C_RES_SUCCESS == i2c_ret)
    {
      sns_smgr_hw.i2c_clk.qupclk_on = enable_flag;
    }
    else
    {
      SNS_SMGR_PRINTF3(FATAL, "set_qup_clk - bus=%d state=%d ret=%d", 
                       i, enable_flag, i2c_ret);
    }
  }
#endif /* !defined(SNS_QDSP_SIM) */
}


/*===========================================================================

  FUNCTION:   sns_hw_timer_cb

===========================================================================*/
/*!
  @brief timer call back. Entered on interrupt
  @param[i]  cb_arg  unused callback argument
  @return   none
 */
/*=========================================================================*/
void sns_hw_timer_cb(void *cb_arg)
{
  sns_smgr_signal_me(SNS_SMGR_PWR_RAIL_SIG);
}

/*===========================================================================

  FUNCTION:   sns_hw_powerrail_status

===========================================================================*/
/*!
  @brief Returns current power rail status
  @param  none
  @return current power rail state
 */
/*=========================================================================*/
sns_pm_pwr_rail_e sns_hw_powerrail_status(void)
{
  return sns_smgr_hw.powerrail_state;
}

/*===========================================================================

  FUNCTION:   sns_hw_qup_clck_status

===========================================================================*/
/*!
  @brief Returns current qup clock status
  @param  none
  @return current qup clock  status
 */
/*=========================================================================*/
bool sns_hw_qup_clck_status(void)
{
  return sns_smgr_hw.i2c_clk.qupclk_on;
}

