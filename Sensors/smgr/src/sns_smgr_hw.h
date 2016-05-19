#ifndef SNS_SMGR_HW_H
#define SNS_SMGR_HW_H
/*=============================================================================
  @file sns_smgr_hw.h
 
  This header file contains the interface between HW and Sensor Manager (SMGR)
 
******************************************************************************   
* Copyright (c) 2014 QUALCOMM Technologies, Inc.  All Rights Reserved
* All Rights Reserved.	  Qualcomm Technologies Confidential and Proprietary
******************************************************************************/

/* $Header: //components/rel/ssc.adsp/2.6.1/smgr/src/sns_smgr_hw.h#1 $ */
/* $DateTime: 2014/12/01 08:57:58 $ */
/* $Author: pwbldsvc $ */

/*============================================================================
  EDIT HISTORY FOR FILE

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2014-10-14  MW   Added sns_hw_pnoc_vote()
  2014-08-26  MW   Made sns_get_i2c_bus_instance() public
  2014-07-31  pn   Enabled power control; removed obsolete code
  2014-06-20  ps   Update sns_i2c_bus_s structure
  2014-06-11  ps   Remove VIRTIO_BRINGUP flag
  2014-05-29  ps   Fixed linux compilation errors 
  2014-05-09  sc   Added changes for uImage I2C driver integration
  2014-04-23  pn   Initial version
  
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "DalDevice.h"

#include "sns_em.h"
#include "sns_reg_common.h"
#include "sns_pm.h"
#include "I2cDriver.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define SNS_SMGR_MAX_GSBI_INSTANCE 13
#define SNS_SMGR_HW_INVALID_GPIO (0xFFFF)

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct  
{
  bool            qupclk_on;
} sns_hw_i2c_clk;

typedef struct {
  int             i2c_bus;
  I2cDrv_I2cBusId i2c_bus_id;
  I2cDrv_I2cBus   config;
} sns_i2c_bus_s;

typedef struct
{
  sns_pm_pwr_rail_e    powerrail_state;
  sns_pm_pwr_rail_e    powerrail_pending_state;
  sns_hw_i2c_clk       i2c_clk;
  sns_em_timer_obj_t   tmr_obj;
  uint16_t             sensor_reset_gpio;
  uint16_t             i2c_sda_1;
  uint16_t             i2c_scl_1;
  uint16_t             i2c_sda_2;
  uint16_t             i2c_scl_2;
  DalDeviceHandle      *gpio_handle;
  DalDeviceHandle      *bus_handle[SNS_SMGR_MAX_GSBI_INSTANCE];
  sns_i2c_bus_s        i2c_bus_instances[SNS_REG_SSI_SMGR_CFG_NUM_SENSORS*SNS_REG_SSI_NUM_SMGR_CFG];
  int                  i2c_bus_count;
} sns_hw_s;


/*----------------------------------------------------------------------------
 *  Variables
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
void sns_get_i2c_bus_instance(const sns_reg_ssi_smgr_cfg_group_drvcfg_s* drv_cfg_ptr);

void sns_hw_set_qup_clk(bool enable_flag);

void sns_hw_control_reset_pin(void);

void sns_hw_power_rail_config(sns_pm_pwr_rail_e enable_flag);

void sns_hw_send_powerrail_msg(sns_pm_pwr_rail_e state);

void sns_hw_bd_config(void);

sns_pm_pwr_rail_e sns_hw_powerrail_status(void);

bool sns_hw_qup_clck_status(void);

void sns_hw_send_powerrail_msg_tmr_cb_proc(void);

void sns_hw_timer_cb(void *cb_arg);

void sns_hw_update_ssi_reg_items(uint16_t Id, uint8_t* data_ptr);

void sns_hw_pnoc_vote(bool on_flag);

#endif /* #ifndef SNS_SMGR_HW_H */
