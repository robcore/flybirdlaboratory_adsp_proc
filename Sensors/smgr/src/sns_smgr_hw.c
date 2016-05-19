/*=============================================================================
  @file sns_smgr_hw.c

  This file contains hw related features used by SMGR.

*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
********************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_hw.c#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-11-19  pn   Only call DAL_DeviceAttach() when necessary
  2014-10-21  jc   Changed sar_int GPIO pin setting
  2014-10-14  MW   Added sns_hw_pnoc_vote()
  2014-10-10  agk  Lowered PNOC BW to more realistic value
  2014-10-02  jhh  Add pnoc vote on/off based on sensor stream activity
  2014-10-02  MW   Fix crash if sns_reset is not used
  2014-09-22  sc   Fix KW error
  2014-09-17  ak   Added i2c GPIO config
  2014-09-15  jms  Added SPI support
  2014-09-08  pn   Moved sns_hw_send_powerrail_msg() from uImage 
  2014-08-26  MW   Made sns_get_i2c_bus_instance() public
  2014-08-08  pn   Processes new SSI registry entries for GPIOs
  2014-07-31  pn   Enabled power control; removed obsolete code
  2014-07-14  VY   Fixed compiler warnings
  2014-06-20  ps   Update sns_i2c_bus_table type
  2014-06-11  ps   Disable I2C GPIO pins configuration
  2014-06-05  vy   Further refactored to support uImage  
  2014-05-09  sc   Added changes for uImage I2C driver integration
  2014-04-23  pn   Initial version
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "DDITlmm.h"

#include "sns_rh_util.h"
#include "sns_smgr_hw.h"
#include "sns_smgr_main.h"
#include "sns_smgr_pm_if.h"
#include "sns_smgr_reg.h"
#include "sns_smgr_util.h"
#include "sns_smgr_ddf_priv.h"

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

static I2cDrv_I2cBusId sns_i2c_bus_table[] =
{
  I2CDRV_I2C_MIN,
  I2CDRV_I2C_1,
  I2CDRV_I2C_2,
  I2CDRV_I2C_3,
  I2CDRV_I2C_4,
  I2CDRV_I2C_5,
  I2CDRV_I2C_6,
  I2CDRV_I2C_7,
  I2CDRV_I2C_8,
  I2CDRV_I2C_9,
  I2CDRV_I2C_10,
  I2CDRV_I2C_11,
  I2CDRV_I2C_12
};


/*----------------------------------------------------------------------------
 *  External Variables/Functions
 * -------------------------------------------------------------------------*/
extern sns_hw_s   sns_smgr_hw;


/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define PNOC_AB  10000  
#define PNOC_IB  10000  


/*===========================================================================

  FUNCTION:   sns_hw_set_inactive_gpio_config

===========================================================================*/
/*!
  @brief Configuring GPIO pins for inactive at DSPS initialization 

  @param [in] gpio_num : the GPIO to configure to inactive state
 
  @return
   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_hw_set_inactive_gpio_config(uint16_t gpio_num, DALGpioPullType pull)
{
#if !defined(SNS_QDSP_SIM)
  DALResult status = DAL_ERROR_INVALID_PARAMETER;

  if ( (gpio_num != SNS_SMGR_HW_INVALID_GPIO) && (gpio_num != 0) 
       && (sns_smgr_hw.gpio_handle != NULL))
  {
    DALGpioSignalType port_config = DAL_GPIO_CFG(gpio_num, 0, DAL_GPIO_INPUT, 
                                                 pull, DAL_GPIO_2MA);
    DalTlmm_SetInactiveConfig(sns_smgr_hw.gpio_handle, gpio_num , port_config);
    status = DalTlmm_ConfigGpio(sns_smgr_hw.gpio_handle, port_config, 
                                DAL_TLMM_GPIO_DISABLE);
  }
  SNS_SMGR_PRINTF2(MED, "set_inactive_gpio - gpio_num=0x%x result=%d", gpio_num, status);
#endif /* !defined(SNS_QDSP_SIM) */
}

/*===========================================================================

  FUNCTION:  sns_smgr_i2c_config 

===========================================================================*/
/*!
  @brief Configuring i2c GPIO pins for the right configuration during sleep and 
  active states.

  @param [in] is_sleep : State of the Vdd IO rail. True implies IO rail is OFF.
 
  @return
   none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_i2c_config(bool is_sleep)
{
  DALResult result = DAL_SUCCESS;
  
  if ( sns_smgr_hw.gpio_handle == NULL )
  {
    SNS_SMGR_PRINTF1(ERROR, "i2c_config - sleep=%u", is_sleep);
    result = DAL_DeviceAttach(DALDEVICEID_TLMM, &sns_smgr_hw.gpio_handle);
  }
  if ( result == DAL_SUCCESS && sns_smgr_hw.gpio_handle != NULL )
  {
    DALGpioSignalType gpio_config;
    DALGpioPullType pull = is_sleep ? DAL_GPIO_PULL_DOWN : DAL_GPIO_PULL_UP;

    gpio_config = DAL_GPIO_CFG(sns_smgr_hw.i2c_sda_1, 4, 
                               DAL_GPIO_OUTPUT, pull, DAL_GPIO_2MA);
    DalTlmm_ConfigGpio(sns_smgr_hw.gpio_handle, gpio_config, DAL_TLMM_GPIO_ENABLE);

    gpio_config = DAL_GPIO_CFG(sns_smgr_hw.i2c_scl_1, 5, 
                               DAL_GPIO_OUTPUT, pull, DAL_GPIO_2MA);
    DalTlmm_ConfigGpio(sns_smgr_hw.gpio_handle, gpio_config, DAL_TLMM_GPIO_ENABLE);

    gpio_config = DAL_GPIO_CFG(sns_smgr_hw.i2c_sda_2, 3, 
                               DAL_GPIO_OUTPUT, pull, DAL_GPIO_2MA);
    DalTlmm_ConfigGpio(sns_smgr_hw.gpio_handle, gpio_config, DAL_TLMM_GPIO_ENABLE);

    gpio_config = DAL_GPIO_CFG(sns_smgr_hw.i2c_scl_2, 3, 
                               DAL_GPIO_OUTPUT, pull, DAL_GPIO_2MA);
    DalTlmm_ConfigGpio(sns_smgr_hw.gpio_handle, gpio_config, DAL_TLMM_GPIO_ENABLE);
  }
}

/*===========================================================================

  FUNCTION:   sns_hw_power_rail_config

===========================================================================*/
/*!
  @brief Power rail state check before sending RPM message

  @detail

  @param[in] state:  the state of power rail needs to be updated to.
  @return
   none
 */
/*=========================================================================*/
void sns_hw_power_rail_config(sns_pm_pwr_rail_e state )
{
#if !defined(SNS_EXCLUDE_POWER)
  uint32_t remaining_time;

  sns_em_timer_get_remaining_time(sns_smgr_hw.tmr_obj, &remaining_time);

  SNS_SMGR_PRINTF3(
     MED, "power_rail_config - curr/want=0x%02x time_remain=%u pending_state=%u",
     (sns_smgr_hw.powerrail_state << 4) | state, 
     remaining_time, sns_smgr_hw.powerrail_pending_state );

  if ( (remaining_time > 0) && (sns_smgr_hw.powerrail_pending_state != state) )
  {
    sns_em_cancel_timer(sns_smgr_hw.tmr_obj);
    remaining_time = 0;
  }

  if ( remaining_time == 0 )
  {
    if ( state > sns_smgr_hw.powerrail_state )
    {
      /* higher power needed now */
      sns_hw_send_powerrail_msg(state);
    }
    else if ( state < sns_smgr_hw.powerrail_state )
    {
      /* lower power needed, can wait */
      if ( SNS_SUCCESS == 
           sns_em_register_timer(sns_smgr_hw.tmr_obj, 
                                 SNS_SMGR_POWERRAIL_HYSTERESIS_TIMER_VALUE_TICK))
      {
        sns_smgr_hw.powerrail_pending_state = state;
      }
      else
      {
        SNS_SMGR_PRINTF0(FATAL, "power_rail_config - failed new timer register");
      }
    }
    /* else, already at the right power state */
  }
  /* else, already waiting to change power to 'state' */
#endif /* !defined(SNS_EXCLUDE_POWER) */
}

/*===========================================================================

  FUNCTION:   sns_get_i2c_bus_instance

===========================================================================*/
/*!
  @brief Read the I2C bus instances from registry and update the max instances
         on this platform.

  @detail

  @param  none
  @return none
 */
/*=========================================================================*/
void sns_get_i2c_bus_instance(
  const sns_reg_ssi_smgr_cfg_group_drvcfg_s* drv_cfg_ptr)
{
  int j, new_bus_instance;
  
  for ( j = 0, new_bus_instance = 1; 
        j < ARR_SIZE(sns_smgr_hw.i2c_bus_instances) && 
        sns_smgr_hw.i2c_bus_instances[j].i2c_bus != 0; 
        j++ ) 
  {
    if(drv_cfg_ptr->i2c_bus == sns_smgr_hw.i2c_bus_instances[j].i2c_bus) 
    {
      new_bus_instance = 0;
      break;
    }
  }
  if ( new_bus_instance && j < ARR_SIZE(sns_smgr_hw.i2c_bus_instances) ) 
  {
    uint8_t bus_idx = (uint8_t)SNS_DDF_COMM_BUS_ID( drv_cfg_ptr->i2c_bus );

    sns_smgr_hw.i2c_bus_instances[j].i2c_bus      = bus_idx;

    if ( bus_idx < ARR_SIZE(sns_i2c_bus_table) )
    {
      sns_smgr_hw.i2c_bus_instances[j].i2c_bus_id = sns_i2c_bus_table[bus_idx];
    } else
    {
      sns_smgr_hw.i2c_bus_instances[j].i2c_bus_id = I2CDRV_I2C_DEV_INVALID;  //bus disabled
    }

    sns_smgr_hw.i2c_bus_count++;

    SNS_SMGR_PRINTF3( MED, "i2c_bus_instance - bus=%d bus_id=%d #bus=%u",
                      bus_idx, sns_smgr_hw.i2c_bus_instances[j].i2c_bus_id,
                      sns_smgr_hw.i2c_bus_count);
  }
}

/*===========================================================================

  FUNCTION:   sns_hw_update_reg_items

===========================================================================*/
/*!
  @brief Updates the registry items for reg group SNS_REG_GROUP_SSI_GPIO_CFG_V02

  @detail

  @param  none
  @return none
 */
/*=========================================================================*/
void sns_hw_update_ssi_reg_items(uint16_t item_id, uint8_t* data_ptr)
{
  if( sns_smgr_ssi_get_cfg_idx(item_id) >= 0 )
  {
    sns_reg_ssi_smgr_cfg_group_s* cfg_group_ptr = 
      (sns_reg_ssi_smgr_cfg_group_s*)data_ptr;
    if( cfg_group_ptr )
    {
      uint32_t ix;
      uint8_t null_uuid[16] = SNS_REG_UUID_NULL;
      for ( ix = 0; ix < ARR_SIZE(cfg_group_ptr->drv_cfg); ix++ )
      {
        sns_reg_ssi_smgr_cfg_group_drvcfg_s* drv_cfg_ptr = &cfg_group_ptr->drv_cfg[ix];
        if( SNS_OS_MEMCMP(drv_cfg_ptr->drvuuid, null_uuid, 16) != 0 )
        {
          SNS_SMGR_PRINTF2(
            MED, "update_ssi_reg - idx=%u sensor=%u", ix, drv_cfg_ptr->sensor_id);
          sns_get_i2c_bus_instance(drv_cfg_ptr);
        }
      }
    }
  }
  else if( item_id == SNS_REG_GROUP_SSI_GPIO_CFG_V02 )
  {
    sns_reg_ssi_gpio_cfg_group_s *cfg_group_ptr = 
      (sns_reg_ssi_gpio_cfg_group_s*)data_ptr;
    if( cfg_group_ptr )
    {
      SNS_SMGR_PRINTF1(
        HIGH, "update_ssi_reg - reset pin = 0x%x", cfg_group_ptr->sns_reset);
      sns_smgr_hw.sensor_reset_gpio = cfg_group_ptr->sns_reset;
      sns_smgr_hw.i2c_sda_1 = cfg_group_ptr->i2c_sda_1;
      sns_smgr_hw.i2c_scl_1 = cfg_group_ptr->i2c_scl_1;
      sns_smgr_hw.i2c_sda_2 = cfg_group_ptr->i2c_sda_2;
      sns_smgr_hw.i2c_scl_2 = cfg_group_ptr->i2c_scl_2;
      sns_hw_control_reset_pin();

      if ( cfg_group_ptr->maj_ver_no >=1 && cfg_group_ptr->min_ver_no >=1 )
      {
        /* version 1.1 or later will have the following entries */
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_test, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_accel_md, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_accel_dri, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_gyro_dri, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_mag_dri, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_alsp_int, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_gest_int, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_press_int, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_sar_int, DAL_GPIO_PULL_DOWN);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_fp_int, DAL_GPIO_NO_PULL);
        sns_hw_set_inactive_gpio_config(cfg_group_ptr->sns_hall_int, DAL_GPIO_NO_PULL);
      }

      if ( SNS_SUCCESS != sns_smgr_req_reg_data( (uint16_t) sns_smgr_ssi_get_cfg_id(0), 
                                                 SNS_SMGR_REG_ITEM_TYPE_GROUP ) )
      {
        SNS_SMGR_PRINTF1(FATAL, "Failed reading registry group %d", 
                         (uint16_t) sns_smgr_ssi_get_cfg_id(0));
      }
    }
  }
}

/*===========================================================================

  FUNCTION:   sns_smgr_hw_read_ssi_data_from_reg

===========================================================================*/
/*!
  @brief Reads the registry items for reg groups SNS_REG_GROUP_SSI_GPIO_CFG_V02 &
         SNS_REG_GROUP_SSI_SMGR_CFG_V02

  @detail

  @param  none
  @return none
 */
/*=========================================================================*/
SMGR_STATIC void sns_smgr_hw_read_ssi_data_from_reg(void)
{
#ifndef ADSP_STANDALONE
  int err = sns_smgr_req_reg_data(SNS_REG_GROUP_SSI_GPIO_CFG_V02, 
                                  SNS_SMGR_REG_ITEM_TYPE_GROUP);
  if ( SNS_SUCCESS == err )
  {
    sns_smgr.all_init_state = SENSOR_ALL_INIT_WAITING_CFG;
  }
  else
  {
    SNS_SMGR_PRINTF2(FATAL, "Failed reading registry. Group %d err %d", 
                     SNS_REG_GROUP_SSI_GPIO_CFG_V02, err);
  }
#else
  sns_smgr_hw.i2c_bus_count = 2;
  sns_smgr_hw.i2c_bus_instances[0].i2c_bus_id = I2CDRV_I2C_5;
  sns_smgr_hw.i2c_bus_instances[1].i2c_bus_id = I2CDRV_I2C_7;
#endif
}

/*===========================================================================

  FUNCTION:   sns_hw_bd_config

===========================================================================*/
/*!
  @brief SMGR init HW related variables

  @detail

  @param  none
  @return none
 */
/*=========================================================================*/
void sns_hw_bd_config(void)
{
  sns_em_create_timer_obj(&sns_hw_timer_cb, NULL, SNS_EM_TIMER_TYPE_ONESHOT, 
                          &sns_smgr_hw.tmr_obj);

#if !defined(SNS_QDSP_SIM)
  sns_smgr_hw.i2c_clk.qupclk_on = false;
  sns_smgr_hw.powerrail_state   = SNS_PWR_RAIL_OFF;
#else
  sns_smgr_hw.i2c_clk.qupclk_on = true;
  sns_smgr_hw.powerrail_state   = SNS_PWR_RAIL_ON_NPM;
#endif

  sns_smgr_hw.gpio_handle       = NULL;
  sns_smgr_hw.sensor_reset_gpio = SNS_SMGR_HW_INVALID_GPIO;
  sns_smgr_hw_read_ssi_data_from_reg();
}


/*===========================================================================

  FUNCTION:   sns_hw_control_reset_pin

===========================================================================*/
/*!
  @brief Configures reset pin 

  @param none
  @return
   none
 */
/*=========================================================================*/
void sns_hw_control_reset_pin(void)
{
#if !defined(SNS_QDSP_SIM)
  DALResult result = DAL_SUCCESS;
  if ( sns_smgr_hw.gpio_handle == NULL )
  {
    result = DAL_DeviceAttach(DALDEVICEID_TLMM, &sns_smgr_hw.gpio_handle);
  }
  if ( (sns_smgr_hw.sensor_reset_gpio != SNS_SMGR_HW_INVALID_GPIO) &&
       (sns_smgr_hw.gpio_handle != NULL) && (result == DAL_SUCCESS) )
  {
    /* configuring sensor reset pin, it will stay high during LD09 and 
       DSPS power on/off, this also puts it in low power mode */

    DALGpioValueType out_val = (sns_smgr_hw.powerrail_state == SNS_PWR_RAIL_OFF) ?
      DAL_GPIO_LOW_VALUE : DAL_GPIO_HIGH_VALUE;
    uint32_t gpio_config =
      DAL_GPIO_CFG_OUT(sns_smgr_hw.sensor_reset_gpio, 0, DAL_GPIO_OUTPUT, 
                       DAL_GPIO_NO_PULL, DAL_GPIO_2MA, out_val);
    DalTlmm_ConfigGpio(sns_smgr_hw.gpio_handle, gpio_config, DAL_TLMM_GPIO_ENABLE);
  }
#endif /* !defined(SNS_QDSP_SIM) */
}

/*===========================================================================

  FUNCTION:   sns_hw_send_powerrail_msg

===========================================================================*/
/*!
  @brief Sending RMP message to change the power state of power rail

  @detail

  @param[in] state:  the state of power rail needs to be updated to.
  @return
   none
 */
/*=========================================================================*/
void sns_hw_send_powerrail_msg(sns_pm_pwr_rail_e state)
{
#if !defined(SNS_QDSP_SIM)

  if ( (state != SNS_PWR_RAIL_OFF) || 
       ((sns_rh_get_report_count() == 0) && 
        (sns_smgr.self_test.self_test_req == NULL)) )
  {
    if ( sns_smgr_pm_vote_powerrail(state) == SNS_SUCCESS )
    {
      sns_pm_pwr_rail_e old_state = sns_smgr_hw.powerrail_state;
      sns_smgr_hw.powerrail_state = state;

      if ( sns_smgr_hw.powerrail_state == SNS_PWR_RAIL_OFF )
      {
        sns_smgr_i2c_config(true);
        sns_hw_control_reset_pin();
        sns_hw_pnoc_vote(false);
        sns_smgr_set_all_sensors_state(SENSOR_STATE_OFF);
      }
      else if ( old_state == SNS_PWR_RAIL_OFF )
      {
        sns_hw_control_reset_pin();
        sns_smgr_i2c_config(false);
        sns_hw_pnoc_vote(true);
      }
      /* else, no change in GPIO config or PNOC between NPM and LPM */
    }
  }
  /* else, cannot turn off power when sensors are streaming or self-test is running */

#endif /* !defined(SNS_QDSP_SIM) */
}

/*===========================================================================

  FUNCTION:   sns_hw_send_powerrail_msg_tmr_cb_proc

===========================================================================*/
/*!
  @brief Power rail timer expired.  It's time to change its state.
  @param    none
  @return   none
 */
/*=========================================================================*/
void sns_hw_send_powerrail_msg_tmr_cb_proc(void)
{
  SNS_SMGR_PRINTF1(
    HIGH, "powerrail_msg_tmr_cb - curr/want=0x%02x", 
    (sns_smgr_hw.powerrail_state << 4) | sns_smgr_hw.powerrail_pending_state);
  sns_hw_send_powerrail_msg(sns_smgr_hw.powerrail_pending_state);
}

/*===========================================================================

  FUNCTION:   sns_hw_pnoc_vote

===========================================================================*/
/*!
  @brief On/Off pnoc vote

  @detail

  @param[in] on_flag: vote on/off flag
  @return
   none
 */
/*=========================================================================*/
void sns_hw_pnoc_vote(bool on_flag)
{
#if !defined(SNS_QDSP_SIM)
  uint8_t     i;
  int32 i2c_ret = I2C_RES_SUCCESS;
  I2cDrvCmdType  pnoc_cmd;
  I2cDrvPnocVoteData vote_data;

  if ( on_flag )
  {
    pnoc_cmd = I2cDrvCmd_Vote_PnocOn;
    vote_data.uPnocAb = PNOC_AB;
    vote_data.uPnocIb = PNOC_IB;
  }
  else
  { 
    pnoc_cmd = I2cDrvCmd_Vote_PnocOff;
    vote_data.uPnocAb = 0;
    vote_data.uPnocIb = 0;
  }

  for ( i=0; i<sns_smgr_hw.i2c_bus_count && i2c_ret==I2C_RES_SUCCESS && 
             i<ARR_SIZE(sns_smgr_hw.i2c_bus_instances); i++ )
  {
    i2c_ret = I2cDrv_Open(sns_smgr_hw.i2c_bus_instances[i].i2c_bus_id, 
                          &(sns_smgr_hw.i2c_bus_instances[i].config), 
                          0);

    i2c_ret = ( (i2c_ret == I2C_RES_SUCCESS) && 
                 I2cDrv_Cmd ( &(sns_smgr_hw.i2c_bus_instances[i].config), 
                             pnoc_cmd, &vote_data) );
  }
#endif /* !defined(SNS_QDSP_SIM) */
}

