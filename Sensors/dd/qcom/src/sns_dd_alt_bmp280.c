/*	Date: 2013/5/28 15:00:00
 *	Revision: 1.1.1
 */


/*******************************************************************************
* Copyright (c) 2013, Bosch Sensortec GmbH
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     1. Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*     2. Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     3. Neither the name of Bosch Sensortec GmbH nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/*
 * @file sns_dd_alt_bmp280.h
 *
 *
 * Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

/*==============================================================================

    S E N S O R S   P R E S S U R E   D R I V E R

DESCRIPTION

   Impelements the driver for the BMP280 driver


                      EDIT HISTORY FOR FILE


when         who     what, where, why
----------   ---     -----------------------------------------------------------
2014-07-22   MW      Eliminate compiler warning
2013-10-18   MW      Fix KW issues
2013-08-20   sc      Fixed compilation warnings.
2013-08-14   lka     Set maximum frequency to 30 Hz.
2013-07012  asr      Generalized support for akm8963/bmp280 i2c slave devices in DMP Passthrough configuration and cleaned up code.
13/07/09    asr      Rearranged the driver code and moved some declarations to header file.
11/26/12    Albert   normal mode get pressure and temperature
03/15/13	Albert   self test

==============================================================================*/


#include "sns_ddf_attrib.h"
#include "sns_ddf_common.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"
#include "sns_dd_alt_bmp280.h"
#include "fixed_point.h"
/*
#include "log_codes.h"
#include "sns_log_types.h"
#include "sns_log_api.h"
*/


#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


sns_ddf_handle_t bmp280_port_handle;
struct bmp280_t *p_bmp280;


/*!
 * @brief list all the standby duration
 * that could be set[unit:ms]
*/
static const uint32_t standbydur_list[] = {\
	1, 63, 125, 250, 500, 1000, 2000, 4000};

/*!
 * @brief list all the sensor operation modes
*/
static const uint8_t op_mode_list[] = {
	BMP_VAL_NAME(SLEEP_MODE),
	BMP_VAL_NAME(FORCED_MODE),
	BMP_VAL_NAME(NORMAL_MODE)
};
/*!
 * @brief list all the sensor work modes
*/
static const uint8_t workmode_list[] = {
	BMP_VAL_NAME(ULTRALOWPOWER_MODE),
	BMP_VAL_NAME(LOWPOWER_MODE),
	BMP_VAL_NAME(STANDARDRESOLUTION_MODE),
	BMP_VAL_NAME(HIGHRESOLUTION_MODE),
	BMP_VAL_NAME(ULTRAHIGHRESOLUTION_MODE)
};

static sns_ddf_status_e sns_dd_alt_bmp280_init(
    sns_ddf_handle_t*        dd_handle_ptr,
    sns_ddf_handle_t         smgr_handle,
    sns_ddf_nv_params_s*     nv_params,
    sns_ddf_device_access_s  device_info[],
    uint32_t                 num_devices,
    sns_ddf_memhandler_s*    memhandler,
    sns_ddf_sensor_e*        sensors[],
    uint32_t*                num_sensors);

static sns_ddf_status_e sns_dd_alt_bmp280_get_data(
    sns_ddf_handle_t        dd_handle,
    sns_ddf_sensor_e        sensors[],
    uint32_t                num_sensors,
    sns_ddf_memhandler_s*   memhandler,
    sns_ddf_sensor_data_s*  data[]);

static sns_ddf_status_e sns_dd_alt_bmp280_set_attr(
    sns_ddf_handle_t     dd_handle,
    sns_ddf_sensor_e     sensor,
    sns_ddf_attribute_e  attrib,
    void*                value);

static sns_ddf_status_e sns_dd_alt_bmp280_get_attr(
    sns_ddf_handle_t       dd_handle,
    sns_ddf_sensor_e       sensor,
    sns_ddf_attribute_e    attrib,
    sns_ddf_memhandler_s*  memhandler,
    void**                 value,
    uint32_t*              num_elems);

static sns_ddf_status_e sns_dd_alt_bmp280_reset(sns_ddf_handle_t dd_handle);
static sns_ddf_status_e sns_dd_alt_bmp280_self_test(
				sns_ddf_handle_t dd_handle,
				sns_ddf_sensor_e sensor,
				sns_ddf_test_e test,
				uint32_t* err);


sns_ddf_driver_if_s sns_alt_bmp280_driver_fn_list =
{
    .init = &sns_dd_alt_bmp280_init,
    .get_data = &sns_dd_alt_bmp280_get_data,
    .set_attrib = &sns_dd_alt_bmp280_set_attr,
    .get_attrib = &sns_dd_alt_bmp280_get_attr,
    .handle_timer = NULL,
    .handle_irq = NULL,
    .reset = &sns_dd_alt_bmp280_reset,
    .run_test = &sns_dd_alt_bmp280_self_test,
    .enable_sched_data = NULL,
    .probe = NULL
};


static sns_ddf_sensor_e bmp280_sensors[] =
{
    SNS_DDF_SENSOR_PRESSURE,
    SNS_DDF_SENSOR_TEMP
};


/*!
 * @brief Mode Prarameters.
 */
static const bmp280_mode_param_t bmp280_mode_param[BMP280_NUM_MODES] =
{
//   usec ,       uA ,  bits ,  oversampling,    noise
    { 5500 ,  3 , 16   , 1 ,  FX_FLTTOFIX_Q16(0.9)}, // ULTRA_LOW_POWER
    { 7500 ,  4 , 17   , 2 ,	 FX_FLTTOFIX_Q16(0.6)},	//LOW_POWER
    {11500 ,  7 , 18   , 4 ,  FX_FLTTOFIX_Q16(0.5)}, // STANDARD
    {19500 ,  12 , 19  , 8 ,  FX_FLTTOFIX_Q16(0.4)}, // HIGH_RESOLUTION
    {37500 ,  25 , 20  , 16 , FX_FLTTOFIX_Q16(0.4)}, // ULTRA_HIGH_RESOLUTION
};


sns_ddf_status_e bmp_read_wrapper(uint8_t dev_addr, uint8_t reg_addr, uint8_t *bosch_read_data, uint8_t len)
{

	sns_ddf_status_e stat;
    uint8_t out;

	if ( (stat = sns_ddf_read_port(bmp280_port_handle,
	                      reg_addr,
	                      bosch_read_data,
	                      len,
	                      &out)) != SNS_DDF_SUCCESS)
	{
		return stat;
	}
	return stat;
}

sns_ddf_status_e bmp_write_wrapper(uint8_t dev_addr, uint8_t reg_addr, uint8_t *bosch_write_buffer, uint8_t len)
{

	sns_ddf_status_e stat;
	uint8_t out;

	if ( (stat = sns_ddf_write_port(bmp280_port_handle,
	                     reg_addr,
	                     bosch_write_buffer,
	                     len,
	                     &out)) != SNS_DDF_SUCCESS)
	{
		return stat;
	}
	return stat;
}
void bmp_delay(uint32_t msec)
{
	sns_ddf_delay(1000*msec);
}


BMP280_RETURN_FUNCTION_TYPE bmp280_init(struct bmp280_t *bmp280)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	p_bmp280 = bmp280;                         /* assign BMP280 ptr */
	p_bmp280->dev_addr = BMP280_I2C_ADDRESS;   /* preset BMP280 I2C_addr */
	comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
		BMP280_CHIPID_REG, &v_data_u8r, 1);    /* read Chip Id */
	p_bmp280->chip_id = v_data_u8r;

	bmp280_get_calib_param(); /* readout bmp280 calibparam structure */
	return comres;
}

BMP280_RETURN_FUNCTION_TYPE bmp280_read_ut(BMP280_S32_t *utemperature)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char a_data_u8r[3] = {0};
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_TEMPERATURE_MSB_REG, a_data_u8r, 3);
		*utemperature = (BMP280_S32_t)((( \
		(BMP280_U32_t) (a_data_u8r[0])) << SHIFT_LEFT_12_POSITION) | \
		(((BMP280_U32_t)(a_data_u8r[1])) << SHIFT_LEFT_4_POSITION) \
		| ((BMP280_U32_t)a_data_u8r[2] >> SHIFT_RIGHT_4_POSITION));
	}
	return comres;
}

/*!
 * @brief  Reads actual temperature from uncompensed temperature
 *							Unit -> Degree Centigrade
 *
 *
 *
 * @param signed long : value of uncompensated temperature
 *
 *
 *
 *  @return signed long : actual temperature
 *
*/
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T)
{
	BMP280_S32_t v_x1_u32r = 0;
	BMP280_S32_t v_x2_u32r = 0;
	BMP280_S32_t temperature = 0;
  if(p_bmp280 == NULL)
  {
     BMP280_ERR_MSG("bmp280_compensate_T_int32: NULL pointer, sensor not initialised?");   
    return temperature;
  }

	v_x1_u32r  = ((((adc_T >> 3) - ((BMP280_S32_t)
		p_bmp280->cal_param.dig_T1 << 1))) * \
		((BMP280_S32_t)p_bmp280->cal_param.dig_T2)) >> 11;
	v_x2_u32r  = (((((adc_T >> 4) - \
		((BMP280_S32_t)p_bmp280->cal_param.dig_T1)) * ((adc_T >> 4) - \
		((BMP280_S32_t)p_bmp280->cal_param.dig_T1))) >> 12) * \
		((BMP280_S32_t)p_bmp280->cal_param.dig_T3)) >> 14;
	p_bmp280->cal_param.t_fine = v_x1_u32r + v_x2_u32r;
	temperature  = (p_bmp280->cal_param.t_fine * 5 + 128) >> 8;

	return temperature;
}

/*!
 * @brief reads uncompensated pressure
 *
 *
 *
 *
 *  @param  unsigned long pressure : Pointer to the data
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_read_up(BMP280_S32_t *upressure)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char a_data_u8r[3] = {0};
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
		BMP280_PRESSURE_MSB_REG, a_data_u8r, 3);
		*upressure = (BMP280_S32_t)((((BMP280_U32_t)(a_data_u8r[0])) \
		<< SHIFT_LEFT_12_POSITION) | (((BMP280_U32_t)(a_data_u8r[1])) \
		<< SHIFT_LEFT_4_POSITION) | ((BMP280_U32_t)a_data_u8r[2] >>\
		SHIFT_RIGHT_4_POSITION));
	}
	return comres;
}

/*!
 * @brief Reads actual pressure from uncompensed pressure
 *							and returns the value in Pascal(Pa)
 *
 *
 *
 *  @param signed long : value of uncompensated pressure
 *
 *
 *
 *  @return
 *			unsigned long : actual pressure
*/
BMP280_U32_t bmp280_compensate_P_int32(BMP280_S32_t adc_P)
{
	BMP280_S32_t v_x1_u32r = 0;
	BMP280_S32_t v_x2_u32r = 0;
	BMP280_U32_t pressure = 0;
  if(p_bmp280 == NULL)
  {
     BMP280_ERR_MSG("bmp280_compensate_P_int32: NULL pointer, sensor not initialised?");
    return pressure;
  }


	v_x1_u32r = (((BMP280_S32_t)p_bmp280->cal_param.t_fine) >> 1) - \
		(BMP280_S32_t)64000;
	v_x2_u32r = (((v_x1_u32r >> 2) * (v_x1_u32r >> 2)) >> 11) * \
		((BMP280_S32_t)p_bmp280->cal_param.dig_P6);
	v_x2_u32r = v_x2_u32r + ((v_x1_u32r * \
		((BMP280_S32_t)p_bmp280->cal_param.dig_P5)) << 1);
	v_x2_u32r = (v_x2_u32r >> 2) + \
		(((BMP280_S32_t)p_bmp280->cal_param.dig_P4) << 16);
	v_x1_u32r = (((p_bmp280->cal_param.dig_P3 * (((v_x1_u32r >> 2) * \
		(v_x1_u32r >> 2)) >> 13)) >> 3) + \
		((((BMP280_S32_t)p_bmp280->cal_param.dig_P2) * \
		v_x1_u32r) >> 1)) >> 18;
	v_x1_u32r = ((((32768+v_x1_u32r)) * \
		((BMP280_S32_t)p_bmp280->cal_param.dig_P1))	>> 15);
	if (v_x1_u32r == 0)
		return 0; /* Avoid exception caused by division by zero */
	pressure = (((BMP280_U32_t)(((BMP280_S32_t)1048576) - adc_P) - \
		(v_x2_u32r >> 12))) * 3125;
	if (pressure < 0x80000000)
		pressure = (pressure << 1) / ((BMP280_U32_t)v_x1_u32r);
	else
		pressure = (pressure / (BMP280_U32_t)v_x1_u32r) * 2;
	v_x1_u32r = (((BMP280_S32_t)p_bmp280->cal_param.dig_P9) * \
		((BMP280_S32_t)(((pressure >> 3) * (pressure >> 3)) >> 13))) \
		>> 12;
	v_x2_u32r = (((BMP280_S32_t)(pressure >> 2)) * \
		((BMP280_S32_t)p_bmp280->cal_param.dig_P8)) >> 13;
	pressure = (BMP280_U32_t)((BMP280_S32_t)pressure + \
		((v_x1_u32r + v_x2_u32r + p_bmp280->cal_param.dig_P7) >> 4));

	return pressure;
}

/*!
 * @brief reads uncompensated pressure and temperature
 *
 *
 *
 *
 *  @param unsigned long utemperature : Address of uncompensated temperature
 *		   unsigned long upressure : Address of uncompensated pressure
 *
 *
 *  @return
 */
BMP280_RETURN_FUNCTION_TYPE bmp280_read_uput(BMP280_S32_t *upressure,\
		BMP280_S32_t *utemperature)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char a_data_u8r[6] = {0};
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
		BMP280_PRESSURE_MSB_REG, a_data_u8r, 6);
		*upressure = (BMP280_S32_t)((((BMP280_U32_t)(a_data_u8r[0])) \
		<< SHIFT_LEFT_12_POSITION) | (((BMP280_U32_t)(a_data_u8r[1])) \
		<< SHIFT_LEFT_4_POSITION) | ((BMP280_U32_t)a_data_u8r[2] >>\
		SHIFT_RIGHT_4_POSITION));

		/* Temperature */
		*utemperature = (BMP280_S32_t)((( \
		(BMP280_U32_t) (a_data_u8r[3])) << SHIFT_LEFT_12_POSITION) | \
		(((BMP280_U32_t)(a_data_u8r[4])) << SHIFT_LEFT_4_POSITION) \
		| ((BMP280_U32_t)a_data_u8r[5] >> SHIFT_RIGHT_4_POSITION));
	}
	return comres;
}

/*!
 * @briefreads pressure and temperature
 *
 *
 *
 *
 *  @param unsigned long temperature : Address of temperature
 *		   unsigned long pressure : Address of pressure
 *
 *
 *  @return
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_read_pt(BMP280_U32_t *pressure,\
		BMP280_S32_t *temperature)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	BMP280_S32_t upressure = 0;
	BMP280_S32_t utemperature = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = bmp280_read_uput(&upressure, &utemperature);
		*temperature = bmp280_compensate_T_int32(utemperature);
		*pressure = bmp280_compensate_P_int32(upressure);
	}
	return comres;
}

/*!
 * @brief reads calibration parameters used for calculation
 *
 *
 *
 *
 *  @param  None
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_calib_param()
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char a_data_u8r[26] = {0};
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_DIG_T1_LSB_REG, a_data_u8r, 24);

		p_bmp280->cal_param.dig_T1 = (BMP280_U16_t)(((\
			(BMP280_U16_t)((unsigned char)a_data_u8r[1])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[0]);
		p_bmp280->cal_param.dig_T2 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[3])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[2]);
		p_bmp280->cal_param.dig_T3 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[5])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[4]);
		p_bmp280->cal_param.dig_P1 = (BMP280_U16_t)(((\
			(BMP280_U16_t)((unsigned char)a_data_u8r[7])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[6]);
		p_bmp280->cal_param.dig_P2 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[9])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[8]);
		p_bmp280->cal_param.dig_P3 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[11])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[10]);
		p_bmp280->cal_param.dig_P4 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[13])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[12]);
		p_bmp280->cal_param.dig_P5 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[15])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[14]);
		p_bmp280->cal_param.dig_P6 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[17])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[16]);
		p_bmp280->cal_param.dig_P7 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[19])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[18]);
		p_bmp280->cal_param.dig_P8 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[21])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[20]);
		p_bmp280->cal_param.dig_P9 = (BMP280_S16_t)(((\
			(BMP280_S16_t)((signed char)a_data_u8r[23])) << \
			SHIFT_LEFT_8_POSITION) | a_data_u8r[22]);
	}
	return comres;
}


BMP280_RETURN_FUNCTION_TYPE bmp280_verify_calib_param()
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	if (p_bmp280 == BMP280_NULL) {
			comres = SNS_DDF_EINVALID_PARAM;
	} else {
				if (!(p_bmp280->cal_param.dig_T1 != 0 || p_bmp280->cal_param.dig_T2 != 0 || p_bmp280->cal_param.dig_T3 != 0 ||
					p_bmp280->cal_param.dig_P1 != 0 || p_bmp280->cal_param.dig_P2 != 0 || p_bmp280->cal_param.dig_P3 != 0 ||
					p_bmp280->cal_param.dig_P4 != 0 || p_bmp280->cal_param.dig_P5 != 0 || p_bmp280->cal_param.dig_P6 != 0 ||
					p_bmp280->cal_param.dig_P7 != 0 || p_bmp280->cal_param.dig_P8 != 0 || p_bmp280->cal_param.dig_P9 != 0))
				{
					comres = SNS_DDF_EFAIL;
				}
	}

	return comres;
}

BMP280_RETURN_FUNCTION_TYPE bmp280_verify_calib_range()
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	if (p_bmp280 == BMP280_NULL) {
			comres = SNS_DDF_EINVALID_PARAM;
	} else {

				if(((p_bmp280->cal_param.dig_T1 < 19000)||(p_bmp280->cal_param.dig_T1 > 35000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_T2 < 22000)||(p_bmp280->cal_param.dig_T2 > 30000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_T3  < -3000)||(p_bmp280->cal_param.dig_T3 > -1000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P1 < 30000)||(p_bmp280->cal_param.dig_P1 > 42000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P2 < -12970)||(p_bmp280->cal_param.dig_P2 > -8000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P3 <-5000)||(p_bmp280->cal_param.dig_P3 > 8000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P4 < -10000)||(p_bmp280->cal_param.dig_P4 > 18000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P5 < -500)||(p_bmp280->cal_param.dig_P5 > 1100)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P6 < -1000)||(p_bmp280->cal_param.dig_P6 > 1000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P7 < -32768)||(p_bmp280->cal_param.dig_P7 > 32767)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P8 < -30000)||(p_bmp280->cal_param.dig_P8 > 10000)))
					comres = SNS_DDF_EFAIL;
				else if(((p_bmp280->cal_param.dig_P9 < -10000)||(p_bmp280->cal_param.dig_P9 > 30000)))
					comres = SNS_DDF_EFAIL;



	}

	return comres;
}


/*!
 * @brief Used to get the Over sampling temperature
 *
 *
 *
 *
 *  @param unsigned char value : Pointer to the osrs_t
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_osrs_t(\
		unsigned char *value)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_OSRST__REG, &v_data_u8r, 1);
		*value = BMP280_GET_BITSLICE(v_data_u8r, \
			BMP280_CTRLMEAS_REG_OSRST);

		p_bmp280->osrs_t = *value;
	}
	return comres;
}

/*!
 * @brief Used to set the Over sampling temperature
 *
 *
 *
 *
 *  @param unsigned char value : Value of the over sampling temperature
 *
 *
 *
 *  @return
 *
 */
BMP280_RETURN_FUNCTION_TYPE bmp280_set_osrs_t(\
	unsigned char value)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_OSRST__REG, &v_data_u8r, 1);
		v_data_u8r = BMP280_SET_BITSLICE(v_data_u8r, \
			BMP280_CTRLMEAS_REG_OSRST, value);
		comres += p_bmp280->BMP280_BUS_WRITE_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_OSRST__REG, &v_data_u8r, 1);

		p_bmp280->osrs_t = value;
	}
	return comres;
}

/*!
 * @brief Used to get the Over sampling pressure
 *
 *
 *
 *
 *  @param  *  \param unsigned char value : Pointer to the value
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_osrs_p(\
	unsigned char *value)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_OSRSP__REG, &v_data_u8r, 1);
		*value = BMP280_GET_BITSLICE(v_data_u8r, \
			BMP280_CTRLMEAS_REG_OSRSP);

		p_bmp280->osrs_p = *value;
	}
	return comres;
}

/*!
 * @brief Used to set the Over sampling pressure
 *
 *
 *
 *
 *  @param unsigned char value : Value of the over sampling pressure
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_set_osrs_p(\
	unsigned char value)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_OSRSP__REG, &v_data_u8r, 1);
		v_data_u8r = BMP280_SET_BITSLICE(v_data_u8r, \
			BMP280_CTRLMEAS_REG_OSRSP, value);
		comres += p_bmp280->BMP280_BUS_WRITE_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_OSRSP__REG, &v_data_u8r, 1);

		p_bmp280->osrs_p = value;
}
	return comres;
}

/*!
 * @brief Used to get the Operational Mode from the sensor
 *
 *
 *
 *
 *  @param  *  \param unsigned char mode : Pointer to the value
 *              0       -> BMP280_SLEEP_MODE
 *              1 and 2 -> BMP280_FORCED_MODE
 *              3       -> BMP280_NORMAL_MODE
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_mode(unsigned char *mode)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_mode_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CTRLMEAS_REG_MODE__REG, &v_mode_u8r, 1);
		*mode = BMP280_GET_BITSLICE(v_mode_u8r, \
			BMP280_CTRLMEAS_REG_MODE);
	}
	return comres;
}

/*!
 * @brief  Used to set the Operational Mode for the sensor
 *
 *
 *
 *
 *  @param unsigned char mode : Value of the mode
 *              0       -> BMP280_SLEEP_MODE
 *              1 and 2 -> BMP280_FORCED_MODE
 *              3       -> BMP280_NORMAL_MODE
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_set_mode(unsigned char mode)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_mode_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		if (mode < BMA280_Four_U8X) {
			v_mode_u8r = (p_bmp280->osrs_t << \
				SHIFT_LEFT_5_POSITION) + (p_bmp280->osrs_p << \
				SHIFT_LEFT_2_POSITION) + mode;
			comres += p_bmp280->BMP280_BUS_WRITE_FUNC(\
				p_bmp280->dev_addr,	\
				BMP280_CTRLMEAS_REG_MODE__REG, &v_mode_u8r, 1);
		} else {
			comres = SNS_DDF_EINVALID_PARAM;
		}
	}
	return comres;
}

/*!
 * @brief Used to reset the sensor
 *
 *
 *
 *
 *  @param
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_set_softreset()
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = BMP280_SOFT_RESET;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = p_bmp280->BMP280_BUS_WRITE_FUNC(p_bmp280->dev_addr, \
			BMP280_RESET_REG, &v_data_u8r, 1);
	}
	return comres;
}

/*!
 * @brief Reads filter setting value
 *
 *
 *
 *
 *  @param  *  \param unsigned char *value : Pointer to value
 *
 *
 *
 *  @return
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_filter(unsigned char *value)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CONFIG_REG_FILTER__REG, &v_data_u8r, 1);
		*value = BMP280_GET_BITSLICE(v_data_u8r, \
			BMP280_CONFIG_REG_FILTER);
	}
	return comres;
}

/*!
 * @brief Writes filter setting to sensor
 *
 *
 *
 *
 *  @param unsigned char value : Value of the filter setting
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_set_filter(unsigned char value)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CONFIG_REG_FILTER__REG, &v_data_u8r, 1);
		v_data_u8r = BMP280_SET_BITSLICE(v_data_u8r, \
			BMP280_CONFIG_REG_FILTER, value);
		comres += p_bmp280->BMP280_BUS_WRITE_FUNC(p_bmp280->dev_addr, \
			BMP280_CONFIG_REG_FILTER__REG, &v_data_u8r, 1);
	}
	return comres;
}

/*!
 * @brief Reads standby duration time from the sensor
 *
 *
 *
 *
 *  @param  *  \param unsigned char *time : Pointer to the time
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_standbydur(unsigned char *time)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CONFIG_REG_TSB__REG, &v_data_u8r, 1);
		*time = BMP280_GET_BITSLICE(v_data_u8r, BMP280_CONFIG_REG_TSB);
	}
	return comres;
}

/*!
 * @brief  Writes standby duration time from the sensor
 *
 *
 *
 *
 *  @param unsigned char time : Value of thestandby duration
 *
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_set_standbydur(unsigned char time)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr, \
			BMP280_CONFIG_REG_TSB__REG, &v_data_u8r, 1);
		v_data_u8r = BMP280_SET_BITSLICE(v_data_u8r, \
			BMP280_CONFIG_REG_TSB, time);
		comres += p_bmp280->BMP280_BUS_WRITE_FUNC(p_bmp280->dev_addr, \
			BMP280_CONFIG_REG_TSB__REG, &v_data_u8r, 1);
	}
	return comres;
}

/*!
 * @brief Writes the working mode to the sensor
 *
 *
 *
 *
 *  @param unsigned char : Mode to be set
 *				0 -> BMP280_ULTRALOWPOWER_MODE
 *				1 -> BMP280_LOWPOWER_MODE
 *				2 -> BMP280_STANDARDRESOLUTION_MODE
 *				3 -> BMP280_HIGHRESOLUTION_MODE
 *				4 -> BMP280_ULTRAHIGHRESOLUTION_MODE
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_set_workmode(unsigned char mode)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_osrst_u8r = 0;
	unsigned char v_osrsp_u8r = 0;
	unsigned char v_data_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		if (mode <= BMA280_Four_U8X) {
			comres += p_bmp280->BMP280_BUS_READ_FUNC(\
				p_bmp280->dev_addr,	BMP280_CTRLMEAS_REG,\
				&v_data_u8r, 1);
			switch (mode) {
			case BMP280_ULTRALOWPOWER_MODE:
				v_osrst_u8r = BMP280_ULTRALOWPOWER_OSRS_T;
				v_osrsp_u8r = BMP280_ULTRALOWPOWER_OSRS_P;
				break;
			case BMP280_LOWPOWER_MODE:
				v_osrst_u8r = BMP280_LOWPOWER_OSRS_T;
				v_osrsp_u8r = BMP280_LOWPOWER_OSRS_P;
				break;
			case BMP280_STANDARDRESOLUTION_MODE:
				v_osrst_u8r = BMP280_STANDARDRESOLUTION_OSRS_T;
				v_osrsp_u8r = BMP280_STANDARDRESOLUTION_OSRS_P;
				break;
			case BMP280_HIGHRESOLUTION_MODE:
				v_osrst_u8r = BMP280_HIGHRESOLUTION_OSRS_T;
				v_osrsp_u8r = BMP280_HIGHRESOLUTION_OSRS_P;
				break;
			case BMP280_ULTRAHIGHRESOLUTION_MODE:
				v_osrst_u8r = BMP280_ULTRAHIGHRESOLUTION_OSRS_T;
				v_osrsp_u8r = BMP280_ULTRAHIGHRESOLUTION_OSRS_P;
				break;
			}
			v_data_u8r = BMP280_SET_BITSLICE(v_data_u8r, \
				BMP280_CTRLMEAS_REG_OSRST, v_osrst_u8r);
			v_data_u8r = BMP280_SET_BITSLICE(v_data_u8r, \
				BMP280_CTRLMEAS_REG_OSRSP, v_osrsp_u8r);
			comres += p_bmp280->BMP280_BUS_WRITE_FUNC(\
				p_bmp280->dev_addr,	BMP280_CTRLMEAS_REG,\
				&v_data_u8r, 1);
		} else {
			comres = SNS_DDF_EINVALID_PARAM;
		}
	}
	return comres;
}

/*!
 * @brief Read both uncompensated temperature and pressure
 *							 in forced mode
 *
 *
 *
 *  @param unsigned long utemperature : Address of uncompensated temperature
 *		   unsigned long pressure : Address of uncompensated pressure
 *
 *
 *  @return
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_get_forced_uput(BMP280_S32_t *upressure,\
		BMP280_S32_t *utemperature)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	unsigned char v_data_u8r = 0;
	unsigned char v_waittime_u8r = 0;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		v_data_u8r = (p_bmp280->osrs_t << SHIFT_LEFT_5_POSITION) + \
			(p_bmp280->osrs_p << SHIFT_LEFT_2_POSITION) + \
			BMP280_FORCED_MODE;
		comres += p_bmp280->BMP280_BUS_WRITE_FUNC(\
				p_bmp280->dev_addr,	BMP280_CTRLMEAS_REG,\
				&v_data_u8r, 1);
		bmp280_compute_wait_time(&v_waittime_u8r);
		p_bmp280->delay_msec(v_waittime_u8r);
		comres += bmp280_read_uput(upressure, utemperature);
	}
	return comres;
}

/*!
 * @brief This API gives data to the given register and
 *                          the data is written in the corresponding register
 *							address
 *
 *
 *
 *  @param unsigned char addr, unsigned char data, unsigned char len
 *          addr -> Address of the register
 *          data -> Data to be written to the register
 *          len  -> Length of the Data
 *
 *
 *
 *  @return communication results.
 *
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_write_register(unsigned char addr,
	    unsigned char *data, unsigned char len)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres = p_bmp280->BMP280_BUS_WRITE_FUNC(p_bmp280->dev_addr,
			addr, data, len);
	}
	return comres;
}

/*!
 * @brief This API reads the data from the given register
 *							address
 *
 *
 *
 *  @param unsigned char addr, unsigned char *data, unsigned char len
 *         addr -> Address of the register
 *         data -> address of the variable, read value will be kept
 *         len  -> Length of the data
 *
 *
 *
 *
 *  @return results of communication routine
 *
 */
BMP280_RETURN_FUNCTION_TYPE bmp280_read_register(unsigned char addr,
		unsigned char *data, unsigned char len)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
	if (p_bmp280 == BMP280_NULL) {
		comres = SNS_DDF_EINVALID_PARAM;
	} else {
		comres += p_bmp280->BMP280_BUS_READ_FUNC(p_bmp280->dev_addr,
			addr, data, len);
	}
	return comres;
}

#ifdef BMP280_ENABLE_FLOAT
/*!
 * @brief Reads actual temperature from uncompensed temperature
 *							and returns the value in Degree centigrade
 *
 *
 *
 *  @param signed long : value of uncompensated temperature
 *
 *
 *
 *  @return
 *			double : actual temperature in floating point
 *
*/
double bmp280_compensate_T_double(BMP280_S32_t adc_T)
{
	double v_x1_u32r = 0;
	double v_x2_u32r = 0;
	double temperature = 0;
  if(p_bmp280 == NULL)
  {
     BMP280_ERR_MSG("bmp280_compensate_T_double: NULL pointer, sensor not initialised?");
    return temperature;
  }

	v_x1_u32r  = (((double)adc_T) / 16384.0 - \
		((double)p_bmp280->cal_param.dig_T1) / 1024.0) * \
		((double)p_bmp280->cal_param.dig_T2);
	v_x2_u32r  = ((((double)adc_T) / 131072.0 - \
		((double)p_bmp280->cal_param.dig_T1) / 8192.0) * \
		(((double)adc_T) / 131072.0 - \
		((double)p_bmp280->cal_param.dig_T1) / 8192.0)) * \
		((double)p_bmp280->cal_param.dig_T3);
	p_bmp280->cal_param.t_fine = (BMP280_S32_t)(v_x1_u32r + v_x2_u32r);
	temperature  = (v_x1_u32r + v_x2_u32r) / 5120.0;


	return temperature;
}

/*!
 * @brief Reads actual pressure from uncompensed pressure
 *							and returns the value in Pascal(Pa)
 *
 *
 *
 *  @param signed int : value of uncompensated pressure
 *
 *
 *
 *  @return
 *			double : actual pressure in floating point
 *
*/
double bmp280_compensate_P_double(BMP280_S32_t adc_P)
{
	double v_x1_u32r = 0;
	double v_x2_u32r = 0;
	double pressure = 0;

   if(p_bmp280 == NULL)
  {
    BMP280_ERR_MSG("bmp280_compensate_P_double: NULL pointer, sensor not initialised?");
    return pressure;
  }


	v_x1_u32r = ((double)p_bmp280->cal_param.t_fine/2.0) - 64000.0;
	v_x2_u32r = v_x1_u32r * v_x1_u32r * \
		((double)p_bmp280->cal_param.dig_P6) / 32768.0;
	v_x2_u32r = v_x2_u32r + v_x1_u32r * \
		((double)p_bmp280->cal_param.dig_P5) * 2.0;
	v_x2_u32r = (v_x2_u32r / 4.0) + \
		(((double)p_bmp280->cal_param.dig_P4) * 65536.0);
	v_x1_u32r = (((double)p_bmp280->cal_param.dig_P3) * \
		v_x1_u32r * v_x1_u32r / 524288.0 + \
		((double)p_bmp280->cal_param.dig_P2) * v_x1_u32r) / 524288.0;
	v_x1_u32r = (1.0 + v_x1_u32r / 32768.0) * \
		((double)p_bmp280->cal_param.dig_P1);
	if (v_x1_u32r == 0.0)
		return 0; /* Avoid exception caused by division by zero */
	pressure = 1048576.0 - (double)adc_P;
	pressure = (pressure - (v_x2_u32r / 4096.0)) * 6250.0 / v_x1_u32r;
	v_x1_u32r = ((double)p_bmp280->cal_param.dig_P9) * \
		pressure * pressure / 2147483648.0;
	v_x2_u32r = pressure * ((double)p_bmp280->cal_param.dig_P8) / 32768.0;
	pressure = pressure + (v_x1_u32r + v_x2_u32r + \
		((double)p_bmp280->cal_param.dig_P7)) / 16.0;

	return pressure;
}
#endif

#if defined(BMP280_ENABLE_INT64) && defined(BMP280_64BITSUPPORT_PRESENT)

/*!
 * @brief Reads actual pressure from uncompensed pressure
 *							and returns the value in Pascal(Pa)
 *
 *
 *
 *  @param signed long : value of uncompensated temperature
 *
 *
 *
 *  @return
 *			unsigned long : actual pressure
*/
BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P)
{
	BMP280_S64_t v_x1_u32r = 0;
	BMP280_S64_t v_x2_u32r = 0;
	BMP280_S64_t pressure = 0;
  if(p_bmp280 == NULL)
  {
    BMP280_ERR_MSG("bmp280_compensate_P_int64: NULL pointer, sensor not initialised?");
    return pressure;
  }

	v_x1_u32r = ((BMP280_S64_t)p_bmp280->cal_param.t_fine) - 128000;
	v_x2_u32r = v_x1_u32r * v_x1_u32r * \
		(BMP280_S64_t)p_bmp280->cal_param.dig_P6;
	v_x2_u32r = v_x2_u32r + ((v_x1_u32r * \
		(BMP280_S64_t)p_bmp280->cal_param.dig_P5) << 17);
	v_x2_u32r = v_x2_u32r + \
		(((BMP280_S64_t)p_bmp280->cal_param.dig_P4) << 35);
	v_x1_u32r = ((v_x1_u32r * v_x1_u32r * \
		(BMP280_S64_t)p_bmp280->cal_param.dig_P3) >> 8) + \
		((v_x1_u32r * (BMP280_S64_t)p_bmp280->cal_param.dig_P2) << 12);
	v_x1_u32r = (((((BMP280_S64_t)1) << 47) + v_x1_u32r)) * \
		((BMP280_S64_t)p_bmp280->cal_param.dig_P1) >> 33;
	if (v_x1_u32r == 0)
		return 0; /* Avoid exception caused by division by zero */
	pressure = 1048576 - adc_P;
	pressure = (((pressure << 31) - v_x2_u32r) * 3125) / v_x1_u32r;
	v_x1_u32r = (((BMP280_S64_t)p_bmp280->cal_param.dig_P9) * \
		(pressure >> 13) * (pressure >> 13)) >> 25;
	v_x2_u32r = (((BMP280_S64_t)p_bmp280->cal_param.dig_P8) * \
		pressure) >> 19;
	pressure = ((pressure + v_x1_u32r + v_x2_u32r) >> 8) + \
		(((BMP280_S64_t)p_bmp280->cal_param.dig_P7) << 4);
	return (BMP280_U32_t)pressure;
}
#endif

/*!
 * @brief Computing waiting time for sensor data read
 *
 *
 *
 *
 *  @param
 *			unsigned char : value of time
 *
 *
 *  @return
*/
BMP280_RETURN_FUNCTION_TYPE bmp280_compute_wait_time(unsigned char \
	*v_delaytime_u8r)
{
	BMP280_RETURN_FUNCTION_TYPE comres = SNS_DDF_SUCCESS;
  if(p_bmp280 == NULL)
  {
    BMP280_ERR_MSG("bmp280_compute_wait_time: NULL pointer, sensor not initialised?");
    return SNS_DDF_EFAIL;
  }

	*v_delaytime_u8r = (T_INIT_MAX + T_MEASURE_PER_OSRS_MAX * \
		(((1 << p_bmp280->osrs_t) >> 1) + ((1 << p_bmp280->osrs_p) \
		>> 1)) + (p_bmp280->osrs_t ? T_SETUP_PRESSURE_MAX : 0) + 15) \
		/ 16;
	return comres;
}



/*!
 * @brief get compersated temperature value
 *
 * @param data the pointer of bmp client data
 * @param temperature the pointer of temperature value
 *
 * @return zero success, non-zero failed
 * @retval zero success
 * @retval non-zero failed
*/
static sns_ddf_status_e bmp_get_temperature(struct bmp_client_data *data, int32_t *temperature)
{
	int32_t utemperature;
	 sns_ddf_status_e err = SNS_DDF_SUCCESS;

	err = BMP_CALL_API(read_ut)(&utemperature);
	if (err)
		return err;
//	*temperature = BMP_CALL_API(compensate_T_double)(utemperature);

	*temperature = BMP_CALL_API(compensate_T_int32)(utemperature);
	return err;
}

/*!
 * @brief get compersated pressure value
 *
 * @param data the pointer of bmp client data
 * @param pressure the pointer of pressure value
 *
 * @return zero success, non-zero failed
 * @retval zero success
 * @retval non-zero failed
*/
static sns_ddf_status_e bmp_get_pressure(struct bmp_client_data *data, uint32_t *pressure)
{
	int32_t temperature;
	int32_t upressure;
	sns_ddf_status_e err = SNS_DDF_SUCCESS;

	/*get current temperature to compersate pressure value
	via global variable p_bmp280->cal_param.t_fine, which defined in sensor function API*/
	err = bmp_get_temperature(data, &temperature);
	if (err)
		return err;

	err = BMP_CALL_API(read_up)(&upressure);
	if (err)
		return err;

	*pressure = BMP_CALL_API(compensate_P_int64)(upressure);
	*pressure = *pressure/256;


	//*pressure = BMP_CALL_API(compensate_P_double)(upressure);
	//	*pressure = BMP_CALL_API(compensate_P_int32)(upressure);
	return err;
}

/*!
 * @brief set operation mode
 *
 * @param data the pointer of bmp client data
 * @param op_mode operation mode need to set
 *
 * @return zero success, non-zero failed
 * @retval zero success
 * @retval non-zero failed
*/
sns_ddf_status_e bmp_set_op_mode(struct bmp_client_data *data, uint8_t op_mode)
{
	sns_ddf_status_e err = SNS_DDF_SUCCESS;
	int i;

	for (i = 0; i < ARRAY_SIZE(op_mode_list); i++) {
		if (op_mode_list[i] == op_mode)
			break;
	}

	if (ARRAY_SIZE(op_mode_list) <= i)
		return SNS_DDF_EFAIL;

	err = BMP_CALL_API(set_mode)(op_mode);
	if (err)
		return err;

	data->op_mode = op_mode;
	return err;
}

/*!
 * @brief set filter coefficient
 *
 * @param data the pointer of bmp client data
 * @param filter filter coefficient need to set
 *
 * @return zero success, non-zero failed
 * @retval zero success
 * @retval non-zero failed
*/
sns_ddf_status_e bmp_set_filter(struct bmp_client_data *data, uint8_t filter)
{
	sns_ddf_status_e err = SNS_DDF_SUCCESS;

	if (filter > BMP_FILTER_MAX)
		filter = BMP_FILTER_MAX;

	err = BMP_CALL_API(set_filter)(filter);
	if (err)
		return err;

	data->filter = filter;
	return err;
}

/*!
 * @brief set standby duration
 *
 * @param data the pointer of bmp client data
 * @param standbydur standby duration need to set
 *
 * @return zero success, non-zero failed
 * @retval zero success
 * @retval non-zero failed
*/
sns_ddf_status_e bmp_set_standbydur(struct bmp_client_data *data, uint32_t standbydur)
{
	sns_ddf_status_e err = SNS_DDF_SUCCESS;
	int i;

	for (i = 0; i < ARRAY_SIZE(standbydur_list); i++) {
		if (standbydur_list[i] == standbydur)
			break;
	}

	if (ARRAY_SIZE(standbydur_list) <= i)
		return SNS_DDF_EFAIL;

	err = BMP_CALL_API(set_standbydur)(i);
	if (err)
		return err;

	data->standbydur = standbydur;
	return err;
}

/*!
 * @brief set work mode, which is defined by software, not hardware.
 * This setting will impact oversampling value of sensor.
 *
 * @param data the pointer of bmp client data
 * @param workmode work mode need to set
 *
 * @return zero success, non-zero failed
 * @retval zero success
 * @retval non-zero failed
*/
sns_ddf_status_e bmp_set_workmode(struct bmp_client_data *data, uint8_t workmode)
	{
		sns_ddf_status_e err = SNS_DDF_SUCCESS;
		int i;
		unsigned char oversampling_t, oversampling_p;

		for (i = 0; i < ARRAY_SIZE(workmode_list); i++) {
			if (workmode_list[i] == workmode)
				break;
		}

		if (ARRAY_SIZE(workmode_list) <= i)
			return SNS_DDF_EFAIL;

		err = BMP_CALL_API(set_workmode)(workmode);
		if (err)
			return err;
		else
			data->workmode = workmode;

		err = BMP_CALL_API(get_osrs_t)(&oversampling_t);
		if (err)
			return err;
		else
			data->oversampling_t = oversampling_t;

		err = BMP_CALL_API(get_osrs_p)(&oversampling_p);
		if (err)
			return err;
		else
			data->oversampling_p = oversampling_p;

		return err;
	}




/*!
 * @brief initialize bmp client
 *
 * @param data the pointer of bmp client data
 *
 * @return SNS_DDF_SUCCESS success, non-zero failed
 * @retval SNS_DDF_SUCCESS success
 * @retval non-zero failed
*/
sns_ddf_status_e bmp_init_client(struct bmp_client_data *data)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;

	status = BMP_CALL_API(init)(&data->device);
	if (status)
		return status;


	status = bmp_set_op_mode(data, BMP_VAL_NAME(SLEEP_MODE));
	if (status)
		return status;

	status = bmp_set_filter(data, BMP_FILTER_DEFAULT);
	if (status)
		return status;

	status = bmp_set_standbydur(data, BMP_STANDBYDUR_DEFAULT);
	if (status)
		return status;

	status = bmp_set_workmode(data, BMP_WORKMODE_DEFAULT);
	return status;
}

/*!
 * @brief Verify the chip id
 *
 * @detail Read the chip id and compare against expected value.
 *
 * @param[in] drv: Pointer to the driver structure.
 *
 * @return
 *  The error code definition within the DDF
 *  SNS_DDF_SUCCESS on success.
*/
sns_ddf_status_e sns_dd_alt_bmp280_check_chip_id(sns_dd_bmp280_state_t *drv)
{
    sns_ddf_status_e status;
    uint8_t chip_id = 0;
    uint8_t read_count = 0;

    status = sns_ddf_read_port(drv->i2c_handle,
                               BMP_REG_NAME(CHIPID_REG),
                               &chip_id, ONE_BYTE, &read_count);

    if (status != SNS_DDF_SUCCESS)
    {
        BMP280_MSG_1(ERROR,"bmp280_check_chip_id: Cannot read i2c port for chip id, i2c handle=%x",drv->i2c_handle);
        return status;
    }
    BMP280_MSG_1(HIGH,"bmp280_check_chip_id: Chip_id=%x",chip_id);

    if ((chip_id != BMP_SENSOR_CHIP_ID)&&(chip_id != BMP_SENSOR_CHIP_ID_2)&&(chip_id != BMP_SENSOR_CHIP_ID_3))
    {
        return SNS_DDF_EDEVICE;
    }

    drv->chip_id = chip_id;

    return SNS_DDF_SUCCESS;
}


/*!
 * @brief Verify the i2c disable switch register 0x87
 *
 * @detail Read the 0x87 address and compare against expected value.
 *
 * @param[in] drv: Pointer to the driver structure.
 *
 * @return
 *  The error code definition within the DDF
 *  SNS_DDF_SUCCESS on success.
*/
static sns_ddf_status_e sns_dd_alt_bmp280_verify_i2c_disable_switch(sns_dd_bmp280_state_t *drv)
{
    sns_ddf_status_e status;
    uint8_t chip_id = 0;
    uint8_t read_count = 0;

    status = sns_ddf_read_port(drv->i2c_handle,
                               0x87,
                               &chip_id, ONE_BYTE, &read_count);

    if (status != SNS_DDF_SUCCESS)
    {
        return status;
    }

    if (chip_id != 0x00)
    {
        return SNS_DDF_EFAIL;
    }


    return SNS_DDF_SUCCESS;
}



/*!
*  @brief Resets the driver and device so they return to the state they were
*         in after init() was called.
*
* @detail
*
* @param[in] drv: pointer to the driver structure
*
* @return
*  The error code definition within the DDF
*  SNS_DDF_SUCCESS on success.
*/

static sns_ddf_status_e sns_dd_alt_bmp280_reset(sns_ddf_handle_t dd_handle)
{

	sns_dd_bmp280_state_t *state = (sns_dd_bmp280_state_t *)dd_handle;

	sns_ddf_status_e status = SNS_DDF_SUCCESS;


	status = BMP_CALL_API(set_softreset)();
	if (status)
	return status;



	sns_ddf_delay(10000);

	return bmp_init_client(&(state->data));

}


/*!
* @brief Initializes the  BMP280
*             determines the device to use
*
*
*  @detail
*   Allocates memory for driver drv structure.
*   Opens the device port by calling sns_ddf_open_port routine
*   Calls sns_dd_alt_bmp280_reset routine
*
*  @param[out] dd_handle_ptr  Pointer that this function must malloc and
*                             populate. This is a handle to the driver
*                            instance that will be passed in to all
*                             other functions.
*  @param[in]  smgr_handle    Handle used to identify this driver when it
*                             calls into Sensors Manager functions.
*  @param[in]  nv_params      NV parameters retrieved for the driver.
*  @param[in]  device_info    Information describing each of the physical
*                             devices controlled by this driver. This is
*                            used to configure the bus and talk to the
*                           device.
*  @param[in]  memhandler     Memory handler used to dynamically allocate
*                            output parameters, if applicable. NB: Do
*                           not use memhandler to allocate memory for
*                           @a dd_handle_ptr.
*  @param[in]  num_devices    Length of @a device_info.
*  @param[out] sensors        List of supported sensors, populated and
*                              returned by this function.
*  @param[out] num_sensors    Length of @a sensors.
*
*  @return
*    The error code definition within the DDF
*    SNS_DDF_SUCCESS on success.
*
*/

static sns_ddf_status_e sns_dd_alt_bmp280_init(
    sns_ddf_handle_t*        dd_handle_ptr,
    sns_ddf_handle_t         smgr_handle,
    sns_ddf_nv_params_s*     nv_params,
    sns_ddf_device_access_s  device_info[],
    uint32_t                 num_devices,
    sns_ddf_memhandler_s*    memhandler,
    sns_ddf_sensor_e*        sensors[],
    uint32_t*                num_sensors)
{
    sns_ddf_status_e status;
    sns_dd_bmp280_state_t *drv;


    status = sns_ddf_malloc((void **)&drv, sizeof(sns_dd_bmp280_state_t));

    if (status != SNS_DDF_SUCCESS)
    {
        return SNS_DDF_ENOMEM;
    }

    memset(drv, 0, sizeof(sns_dd_bmp280_state_t));

    drv->smgr_handle = smgr_handle;

    status = sns_ddf_open_port(&(drv->i2c_handle),
                               &(device_info->port_config));

    if (status != SNS_DDF_SUCCESS)
    {
        BMP280_MSG_0(ERROR,"bmp280_init: Cannot open i2c port");
        goto port_err;
    }
	bmp280_port_handle = drv->i2c_handle;

    status = sns_dd_alt_bmp280_check_chip_id(drv);

    if (status != SNS_DDF_SUCCESS)
    {
      BMP280_MSG_0(ERROR,"bmp280_init: Chip id failure.");
        goto init_err;
    }

	drv->data.device.bus_read = bmp_read_wrapper;
	drv->data.device.bus_write = bmp_write_wrapper;
	drv->data.device.delay_msec = bmp_delay;

	drv->mode = BMP280_MODE_STANDARD;

	/* Initialize the BMP chip */
    status = bmp_init_client(&(drv->data));

    if (status != SNS_DDF_SUCCESS)
    {
        BMP280_MSG_0(ERROR,"bmp280_init: bmp_init_client_failed..");
        goto init_err;
    }


    /* Fill out supported sensor info */
    *num_sensors = 2;
    *sensors = bmp280_sensors;

    *dd_handle_ptr = (sns_ddf_handle_t) drv;


    if (status != SNS_DDF_SUCCESS)
    {
        goto init_err;
    }


    return SNS_DDF_SUCCESS;

init_err:

    sns_ddf_close_port(drv->i2c_handle);
port_err:
    sns_ddf_mfree(drv);

    return status;
}



/*!
*  @brief Sets the BOSCH magnetometer  to the passed in operating mode
*
*  @detail
*  Set the operational mode (sleep or nornal)
*
*  @param[in] state: Ptr to the driver structure
*  @param[in] mode: Ptr to the variable of sns_ddf_powerstate_e type
*
*  @return
*   The error code definition within the DDF
*    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
*
*/

static sns_ddf_status_e sns_dd_bmp280_config_mode
(
   sns_dd_bmp280_state_t *state,
   sns_ddf_powerstate_e      *mode
)
{
   sns_ddf_status_e status = SNS_DDF_SUCCESS;

   switch (*mode)
   {
   case SNS_DDF_POWERSTATE_ACTIVE://normal
   		if( (status = bmp_set_op_mode(&(state->data), BMP280_NORMAL_MODE)) != SNS_DDF_SUCCESS)
		 {
		   return status;
		 }
		 break;

   case SNS_DDF_POWERSTATE_LOWPOWER://suspend
	   if( (status = bmp_set_op_mode(&(state->data), BMP280_SLEEP_MODE)) != SNS_DDF_SUCCESS)
				{
				  return status;
				}
				break;

      break;
   default:
      return status;

   }



   return SNS_DDF_SUCCESS;
}



/*!
*  @brief Sets an attribute of the bmp280
*
* @detail
*    Called by SMGR to set certain device attributes that are
*    programmable. Curently its the power mode and range.
*
*  @param[in] dd_handle   Handle to a driver instance.
*  @param[in] sensor Sensor for which this attribute is to be set.
*  @param[in] attrib      Attribute to be set.
*  @param[in] value      Value to set this attribute.
*
*  @return
*   The error code definition within the DDF
*    SNS_DDF_SUCCESS on success.
*
*/

static sns_ddf_status_e sns_dd_alt_bmp280_set_attr(
    sns_ddf_handle_t     dd_handle,
    sns_ddf_sensor_e     sensor,
    sns_ddf_attribute_e  attrib,
    void*                value_ptr)
{
	 sns_ddf_status_e ret_val = SNS_DDF_SUCCESS;

    if ((sensor != SNS_DDF_SENSOR_PRESSURE) && (sensor != SNS_DDF_SENSOR__ALL))
    {
        BMP280_ERR_MSG("invalid sensor");
        return SNS_DDF_EINVALID_PARAM;
    }

    switch (attrib)
    {
    case SNS_DDF_ATTRIB_POWER_STATE:

       ret_val = sns_dd_bmp280_config_mode((sns_dd_bmp280_state_t*)dd_handle,
                                           (sns_ddf_powerstate_e *)value_ptr);
        break;
    case SNS_DDF_ATTRIB_RANGE:

        break;
    case SNS_DDF_ATTRIB_LOWPASS:

        break;
    case SNS_DDF_ATTRIB_RESOLUTION_ADC:

        break;

    default:
        BMP280_ERR_MSG("invalid attrib");
        return SNS_DDF_EINVALID_ATTR;
    }

    return ret_val;
}


/*!
*  @brief Called by the SMGR to retrieves the value of an attribute of
*  the sensor.
*
*  @detail
*   range and resolution info is from the device data sheet.
*
*  @param[in] dd_handle   Handle to a driver instance.
*  @param[in] sensor       Sensor whose attribute is to be retrieved.
*  @param[in] attrib      Attribute to be retrieved.
*  @param[in] memhandler  Memory handler used to dynamically allocate
*                         output parameters, if applicable.
*  @param[out] value      Pointer that this function will allocate or set
*                         to the attribute's value.
*  @param[out] num_elems  Number of elements in @a value.
*
*  @return
*    The error code definition within the DDF
*    SNS_DDF_SUCCESS on success.
*
*/


static sns_ddf_status_e sns_dd_alt_bmp280_get_attr(
    sns_ddf_handle_t       dd_handle,
    sns_ddf_sensor_e       sensor,
    sns_ddf_attribute_e    attrib,
    sns_ddf_memhandler_s*  memhandler,
    void**                 value,
    uint32_t*              num_elems)
{
    sns_dd_bmp280_state_t *drv = (sns_dd_bmp280_state_t *)dd_handle;

    if ((sensor != SNS_DDF_SENSOR_PRESSURE) && (sensor != SNS_DDF_SENSOR__ALL))
    {
        BMP280_ERR_MSG("invalid sensor");
        return SNS_DDF_EINVALID_PARAM;
    }

    switch (attrib)
    {
    case SNS_DDF_ATTRIB_POWER_INFO:
        {
            sns_ddf_power_info_s* power_attrib;
            power_attrib = sns_ddf_memhandler_malloc(memhandler,
                                                     sizeof(sns_ddf_power_info_s));
            if (power_attrib == NULL)
            {
                BMP280_ERR_MSG("malloc failure power_attrib");
                return SNS_DDF_ENOMEM;
            }

            power_attrib->active_current = bmp280_mode_param[drv->mode].avg_current_uA;


            power_attrib->lowpower_current = 0;
            *num_elems = 1;
            *value = power_attrib;
        }
        break;

    case SNS_DDF_ATTRIB_RANGE:
        {
            sns_ddf_range_s *device_ranges;

            device_ranges = sns_ddf_memhandler_malloc(memhandler,
                                                      sizeof(sns_ddf_range_s));
            if (device_ranges == NULL)
            {
                BMP280_ERR_MSG("malloc failure device_ranges");
                return SNS_DDF_ENOMEM;
            }

			*num_elems = 1;

            if (sensor == SNS_DDF_SENSOR_PRESSURE)
            {
                /*
                 * Pressure Range is 300 to 1100 hPa = 30,000 to 110,000 Pascals.
                 * Which is +9000 meters to -500 meters at sea level.
                 * Pressure at sea level is 1013.25 hPa.
                 * A pressure change of 1 hPa (100 Pascals) corresponds to 8.43 meters
                 * at sea level.
                 */
                device_ranges[0].min = FX_FLTTOFIX_Q16(300.0);
                device_ranges[0].max = FX_FLTTOFIX_Q16(1100.0);
            }

            if (sensor == SNS_DDF_SENSOR_TEMP)
            {
                /*
                 *  Temperature Operational range is -40°C to +85°C.
                 *  Full Accuracy range is 0°C to +65°C.
                 */
                device_ranges[0].min = FX_FLTTOFIX_Q16(-40.0 * G);
                device_ranges[0].max = FX_FLTTOFIX_Q16( 85.0 * G);
            }

            *value = device_ranges;
        }
        break;

    case SNS_DDF_ATTRIB_RESOLUTION_ADC:
        {
            sns_ddf_resolution_adc_s* resp;
            if ( (resp = sns_ddf_memhandler_malloc(memhandler, sizeof(sns_ddf_resolution_adc_s))) == NULL )
            {
                 return SNS_DDF_ENOMEM;
            }
            *num_elems = 1;

            resp->bit_len = bmp280_mode_param[drv->mode].bits;
            resp->max_freq = 30;
            *value = resp;
        }
        break;

    case SNS_DDF_ATTRIB_RESOLUTION:
        {
            sns_ddf_resolution_t *device_res;
            int res_num = 1;

            device_res = sns_ddf_memhandler_malloc(memhandler,
                                                   res_num*sizeof(sns_ddf_resolution_t));

            if (device_res == NULL)
            {
                BMP280_ERR_MSG("malloc failure device_res");
                return SNS_DDF_ENOMEM;
            }

            *num_elems = res_num;

            if (sensor == SNS_DDF_SENSOR_PRESSURE)
            {
                device_res[0] = bmp280_pressure_resolution; /* 0.01 hPa */
            }

            if (sensor == SNS_DDF_SENSOR_TEMP)
            {
                device_res[0] = bmp280_temperature_resolution; /* 0.01°C */
            }

            *value = device_res;
        }
        break;

    case SNS_DDF_ATTRIB_LOWPASS:

        return SNS_DDF_EINVALID_PARAM;

    case SNS_DDF_ATTRIB_DELAYS:

        break;


    case SNS_DDF_ATTRIB_DEVICE_INFO:
        {
            sns_ddf_device_info_s *device_info;
            device_info = sns_ddf_memhandler_malloc(memhandler,
                                                    sizeof(sns_ddf_device_info_s));
            if (device_info == NULL)
            {
                BMP280_ERR_MSG("malloc failure device_info");
                return SNS_DDF_ENOMEM;
            }

            device_info->vendor = "BOSCH";
            device_info->model = "BMP280";
            device_info->name = "Pressure";
            device_info->version = 1;

            *value = device_info;
            *num_elems = 1;
        }
        break;

    default:
        BMP280_ERR_MSG("invalid attrib");
        return SNS_DDF_EINVALID_ATTR;
    }

    return SNS_DDF_SUCCESS;
}


/*!
*  @brief Called by the SMGR to get data
*
*  @detail
*   Requests a single sample of sensor data from each of the specified
*    sensors.
*
*  @param[in] dd_handle     Handle to a driver instance.
*  @param[in] sensors       List of sensors for which data isrequested.
*  @param[in] num_sensors   Length of @a sensors.
*  @param[in] memhandler    Memory handler used to dynamically allocate
*                           output parameters, if applicable.
*  @param[out] data         Sampled sensor data. The number of elements
*                           must match @a num_sensors.
*
*  @return
*    The error code definition within the DDF
*    SNS_DDF_SUCCESS on success.
*
*/


static sns_ddf_status_e sns_dd_alt_bmp280_get_data
(
  sns_ddf_handle_t        dd_handle,
  sns_ddf_sensor_e        sensors[],
  uint32_t                num_sensors,
  sns_ddf_memhandler_s*   memhandler,
  sns_ddf_sensor_data_s*  data[]
)

{
  uint8_t i;
  sns_ddf_status_e status = SNS_DDF_SUCCESS;
  sns_ddf_sensor_data_s *data_ptr;

  sns_dd_bmp280_state_t *state = (sns_dd_bmp280_state_t *)dd_handle;
  uint32_t pressure = 0;
  int32_t temperature = 0;

  for (i = 0; i < num_sensors; i++)
  {
    if (sensors[i] != SNS_DDF_SENSOR_PRESSURE &&
        sensors[i] != SNS_DDF_SENSOR_TEMP)
    {
      return SNS_DDF_EINVALID_PARAM;
    }
  }


  if( (data_ptr = sns_ddf_memhandler_malloc(memhandler,
        (num_sensors)*(sizeof(sns_ddf_sensor_data_s)))) == NULL)
  {
    return SNS_DDF_ENOMEM;
  }


  *data = data_ptr;

  for (i=0; i <num_sensors; i++)
  {
    data_ptr[i].sensor = sensors[i];
    data_ptr[i].status = SNS_DDF_SUCCESS;
    data_ptr[i].timestamp = sns_ddf_get_timestamp();

    if (sensors[i] == SNS_DDF_SENSOR_PRESSURE)
    {
      if( (data_ptr[i].samples = sns_ddf_memhandler_malloc(memhandler,
            sizeof(sns_ddf_sensor_sample_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }
	  status = bmp_get_pressure(&(state->data), &pressure);

	  data_ptr[i].samples[0].sample  = pressure*bmp280_pressure_resolution;
      data_ptr[i].samples[0].status = SNS_DDF_SUCCESS;
      data_ptr[i].num_samples = 1;

    }
    else // TEMPER sensor
    {
      if( (data_ptr[i].samples = sns_ddf_memhandler_malloc(memhandler,
                                   sizeof(sns_ddf_sensor_sample_s))) == NULL)
      {
        return SNS_DDF_ENOMEM;
      }

	  status = bmp_get_temperature(&(state->data), &temperature);

      data_ptr[i].samples[0].sample = temperature*bmp280_temperature_resolution;
      data_ptr[i].samples[0].status = SNS_DDF_SUCCESS;
      data_ptr[i].num_samples = 1;
     }
  }




  return status;
}

static sns_ddf_status_e sns_dd_alt_bmp280_self_test(
				sns_ddf_handle_t dd_handle,
				sns_ddf_sensor_e sensor,
				sns_ddf_test_e test,
				uint32_t* err)
{
	sns_dd_bmp280_state_t *state = (sns_dd_bmp280_state_t *)dd_handle;
	sns_ddf_status_e status;

	uint32_t pressure;
	int32_t temperature;


	/*! set sensor to normal mode */
	status = bmp_set_op_mode(&(state->data), BMP280_NORMAL_MODE);
	if (status != SNS_DDF_SUCCESS)
	 {
		  return status;
	 }

	sns_ddf_delay(5000);

	/*! Verify the chip id */
    status = sns_dd_alt_bmp280_check_chip_id(state);

    if (status != SNS_DDF_SUCCESS)
    {
         return status;
    }

	/*! verify the value in register address 0x87 is set to 0x00 */
	status = sns_dd_alt_bmp280_verify_i2c_disable_switch(state);

    if (status != SNS_DDF_SUCCESS)
    {
         return status;
    }


	/*! readout bmp280 calibparam structure */
	status = bmp280_get_calib_param();

	if (status != SNS_DDF_SUCCESS)
    {
         return status;
    }


	/*! check whether all calibration parameters are 0 */
	status = bmp280_verify_calib_param();

	if (status != SNS_DDF_SUCCESS)
    {
         return status;
    }


	/*! check whether all calibration parameters are within range */
	status = bmp280_verify_calib_range();

	if (status != SNS_DDF_SUCCESS)
    {
         return status;
    }


	status = bmp280_set_osrs_p(BMP280_ULTRALOWPOWER_OSRS_P);

	if (status != SNS_DDF_SUCCESS)
	{
		 return status;
	}

	status = bmp280_set_osrs_t(BMP280_ULTRALOWPOWER_OSRS_T);

	if (status != SNS_DDF_SUCCESS)
	{
		 return status;
	}

	status = bmp_set_op_mode(&(state->data), BMP280_FORCED_MODE);

	if (status != SNS_DDF_SUCCESS)
	{
		 return status;
	}

	sns_ddf_delay(5000);


	status = bmp_get_pressure(&(state->data), &pressure);

	if (status != SNS_DDF_SUCCESS)
	{
		 return status;
	}

	/*! value of pressure must be in the range 900hPa < pressure < 1100hPa */
	if ((pressure*0.01 <= 900)||(pressure*0.01 >= 1100))
	{
		 return SNS_DDF_EFAIL;
	}

	status = bmp_get_temperature(&(state->data), &temperature);

	if (status != SNS_DDF_SUCCESS)
	{
		 return status;
	}

	/*! value of temperature must be in the range 0C < pressure < 40C */
	if ((temperature*0.01 <= 0)||(temperature*0.01 >= 40))
	{
		 return SNS_DDF_EFAIL;
	}


	sns_ddf_smgr_notify_test_complete(((sns_dd_bmp280_state_t *)dd_handle)->smgr_handle,
	sensor, status, *err);

	return status;


}


