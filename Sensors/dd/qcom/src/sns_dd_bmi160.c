/*******************************************************************************
 * Copyright (c) 2014, Bosch Sensortec GmbH
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

 /****************************************************************************
  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential
  ****************************************************************************/

#include "sns_dd_bmi160.h"
#include "sns_dd_bmi160_priv.h"


extern
sns_ddf_handle_t bmi160_sns_port_handle_singleton;



static const sns_ddf_sensor_e BMI160_FIFO_SENSOR_LIST[] = {
	SNS_DDF_SENSOR_ACCEL,
	SNS_DDF_SENSOR_GYRO,
#if BMI160_CONFIG_ENABLE_MAG_IF
	SNS_DDF_SENSOR_MAG,
#endif
};

#if BMI160_CONFIG_RUN_ON_OSSC_V1
static int32_t bmi160_sensor_list_sub_dev_idx = 0;
static sns_ddf_sensor_e bmi160_sensor_list_sub_devs[BMI160_MAX_SUB_DEV_NUM][BMI160_MAX_SENSORS_NUM] =
{
	{
		SNS_DDF_SENSOR_ACCEL,
	},

	{
		SNS_DDF_SENSOR_GYRO,
		SNS_DDF_SENSOR_TEMP,
	},

	{
		SNS_DDF_SENSOR_DOUBLETAP
	},

#if BMI160_CONFIG_ENABLE_MAG_IF
	{
		SNS_DDF_SENSOR_MAG
	},
#endif

};
#endif

/* !global variables */
//CAUTION: don't change the order of the elements in this list
static const uint32_t BMI160_ACC_RANGE_REGV_LIST[] =
{
	BMI160_REGV_ACC_RANGE_PM2G,
	BMI160_REGV_ACC_RANGE_PM4G,
	BMI160_REGV_ACC_RANGE_PM8G,
	BMI160_REGV_ACC_RANGE_PM16G
};

//CAUTION: don't change the order of the elements in this list
static const uint32_t BMI160_GYR_RANGE_REGV_LIST[] =
{
	BMI160_REGV_GYR_RANGE_PM125DPS,
	BMI160_REGV_GYR_RANGE_PM250DPS,
	BMI160_REGV_GYR_RANGE_PM500DPS,
	BMI160_REGV_GYR_RANGE_PM1000DPS,
	BMI160_REGV_GYR_RANGE_PM2000DPS
};

//CAUTION: don't change the order of the elements in this list
static const uint32_t BMI160_ACC_BW_DELAY_TIME[8] =
{
	40000, // BMI160_REGV_ODR_25HZ
	20000, // BMI160_REGV_ODR_50HZ
	10000, // BMI160_REGV_ODR_100HZ
	5000,  // BMI160_REGV_ODR_200HZ
	3000,  // BMI160_REGV_ODR_400HZ
	2000,  // BMI160_REGV_ODR_800HZ
	1000,  // BMI160_REGV_ODR_1600HZ
};

#if 0
static const uint32_t BMI160_ACC_FREQ_LIST[12] =
{
	FX_FLTTOFIX_Q16(25.0/2),
	FX_FLTTOFIX_Q16(50.0/2),
	FX_FLTTOFIX_Q16(100.0/2),
	FX_FLTTOFIX_Q16(200.0/2),
	FX_FLTTOFIX_Q16(400.0/2),
	FX_FLTTOFIX_Q16(800.0/2),
	FX_FLTTOFIX_Q16(1600.0/2),
};


static const uint32_t BMI160_GYR_FREQ_LIST[8] =
{
	FX_FLTTOFIX_Q16(25.0/2),
	FX_FLTTOFIX_Q16(50.0/2),
	FX_FLTTOFIX_Q16(100.0/2),
	FX_FLTTOFIX_Q16(200.0/2),
	FX_FLTTOFIX_Q16(400.0/2),
	FX_FLTTOFIX_Q16(800.0/2),
	FX_FLTTOFIX_Q16(1600.0/2),
};
#endif


/*! reported Temprature resolution is 1 C (Celsius) */


//this list contains the ODRs that are common to accel and gyr
//CAUTION: don't change the order of the elements in this list
static struct bst_val_pair BMI160_REGV_ODR_MAP[] =
{
	//12.5 does not work for gyr, so the minimum is 25HZ
	{
		.l = 25,
		.r = BMI160_REGV_ODR_25HZ
	},

	{
		.l = 50,
		.r = BMI160_REGV_ODR_50HZ
	},

	{
		.l = 100,
		.r = BMI160_REGV_ODR_100HZ
	},

	{
		.l = 200,
		.r = BMI160_REGV_ODR_200HZ
	},

	{
		.l = 400,
		.r = BMI160_REGV_ODR_400HZ
	},

	{
		.l = 800,
		.r = BMI160_REGV_ODR_800HZ
	},

	{
		.l = 1600,
		.r = BMI160_REGV_ODR_1600HZ
	},
};


static sns_dd_bmi160_head_t bmi160_sns_dd_list_head = {
	NULL,
	{"BOSCH BMI160 Driver", 1}
};


/*=======================================================================

  INTERNAL FUNCTION PROTOTYPES

  ========================================================================*/


/*! forward declarations of global/static variables */
extern sns_ddf_driver_if_s SNS_DD_IF_BMI160;


/*! forward declarations of global/static functions */
static sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_set_range(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 range_idx);

static sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_set_power_state(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		sns_ddf_powerstate_e    power_state);


static sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_get_best_match_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                odr_req,
		sns_ddf_odr_t           *odr_matched);

sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_set_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 odr_regv);


static sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_set_range(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 range_idx);

static sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_set_power_state(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		sns_ddf_powerstate_e    power_state);


static sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_get_best_match_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                odr_req,
		sns_ddf_odr_t           *odr_matched);

sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_set_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 odr_regv);


static sns_ddf_status_e sns_dd_bmi160_cfg_int_md(
		sns_dd_bmi160_state_t  *state,
		bool                   enable);


#if BMI160_CONFIG_ENABLE_MAG_IF
static sns_ddf_status_e sns_dd_bmi160_hw_mod_mag_set_power_state(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		sns_ddf_powerstate_e    power_state);


static sns_ddf_status_e sns_dd_bmi160_hw_mod_mag_get_best_match_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                odr_req,
		sns_ddf_odr_t           *odr_matched);

sns_ddf_status_e sns_dd_bmi160_hw_mod_mag_set_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 odr_regv);
#endif


static sns_ddf_status_e sns_dd_bmi160_cfg_md_thresh(
		sns_dd_bmi160_state_t  *state);

#if BMI160_CONFIG_ENABLE_MD
static sns_ddf_status_e sns_dd_bmi160_cfg_md_dur(
		sns_dd_bmi160_state_t  *state);
#endif

static sns_ddf_status_e sns_dd_bmi160_soft_reset_and_cfg_default(
		sns_dd_bmi160_state_t *state);

uint32_t bmi160_util_get_com_div(int32_t a, int32_t b)
{
	uint32_t mcd = 1;
	int32_t  r;
	int32_t  t;

	if (a < 0) {
		a = -a;
	}

	if (b < 0) {
		b = -b;
	}

	if (a < b) {
		t = a;
		a = b;
		b = t;
	}

	if (0 == a) {
		return b;
	}

	if (0 == b) {
		return a;
	}

	while (1) {
		mcd = b;
		r = a % b;

		if (0 != r) {
			a = b;
			b = r;
		} else {
			break;
		}
	}

	return mcd;
}

inline
void bmi160_udelay(uint32_t us)
{
	sns_ddf_delay(us);
}

//reviewed
static sns_ddf_status_e bmi160_check_chip_id(
		sns_ddf_handle_t        port_handle,
		uint16_t                *chip_rev)
{
	int32_t status;
	uint8_t si_buf_rd[2] = "";

	bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_CHIP_ID,
			si_buf_rd,
			1);
	bmi160_udelay(1000);

	status = bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_CHIP_ID,
			si_buf_rd,
			2);

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (BMI160_REGV_CHIP_ID_MAJOR != (si_buf_rd[0] & BMI160_REGV_CHIP_ID_MAJOR)) {
		status = SNS_DDF_EDEVICE;
	}

	*chip_rev = (si_buf_rd[0] << 8) | si_buf_rd[1];

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e bmi160_acc_get_range_idx(
		sns_ddf_handle_t port_handle,
		int32_t *idx)
{
	sns_ddf_status_e status;
	int32_t i;
	uint8_t si_buf_rd;
	uint8_t range;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_ACC_RANGE,
			&si_buf_rd, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	range = BST_GET_VAL_BITBLOCK(si_buf_rd, 0, 3);
	for (i = 0; i < BST_ARRAY_SIZE(BMI160_ACC_RANGE_REGV_LIST); i++) {
		if (BMI160_ACC_RANGE_REGV_LIST[i] == range) {
			*idx = i;
			return SNS_DDF_SUCCESS;
		}
	}

	*idx = -1;

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e bmi160_gyr_get_range_idx(
		sns_ddf_handle_t port_handle,
		int32_t *idx)
{
	sns_ddf_status_e status;
	int32_t i;
	uint8_t si_buf_rd;
	uint8_t range;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_GYR_RANGE,
			&si_buf_rd, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	range = BST_GET_VAL_BITBLOCK(si_buf_rd, 0, 2);
	for (i = 0; i < BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST); i++) {
		if (BMI160_GYR_RANGE_REGV_LIST[i] == range) {
			*idx = i;
			return SNS_DDF_SUCCESS;
		}
	}

	*idx = -1;

	return SNS_DDF_SUCCESS;
}


static sns_ddf_status_e bmi160_get_curr_odr_map_idx(
		sns_ddf_handle_t        port_handle,
		sns_ddf_sensor_e        sensor_type,
		int32_t                 *idx)
{
	sns_ddf_status_e status;
	uint8_t rega;
	uint8_t regv;
	uint8_t si_buf_rd;
	uint8_t i;

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			rega = BMI160_REGA_USR_ACC_CONF;
			break;
		case SNS_DDF_SENSOR_GYRO:
			rega = BMI160_REGA_USR_GYR_CONF;
			break;
		case SNS_DDF_SENSOR_MAG:
			rega = BMI160_REGA_USR_MAG_CONF;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	status = bmi160_sbus_read_wrapper(port_handle,
			rega, &si_buf_rd, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	regv = BST_GET_VAL_BITBLOCK(si_buf_rd, 0, 3);
	for (i = 0; i < BST_ARRAY_SIZE(BMI160_REGV_ODR_MAP); i++) {
		if (BMI160_REGV_ODR_MAP[i].r == regv) {
			*idx = i;
			return SNS_DDF_SUCCESS;
		}
	}

	*idx = -1;
	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e bmi160_get_reg_pmu_status(
		sns_ddf_handle_t                port_handle,
		bmi160_pmu_stat_reg_t           *stat_reg)
{
	sns_ddf_status_e status;
	uint8_t si_buf_rd;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_PMU_STATUS,
			&si_buf_rd,
			1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	stat_reg->bits.mag_pmu_status = BST_GET_VAL_BITBLOCK(si_buf_rd, 0, 1);
	stat_reg->bits.gyr_pmu_status = BST_GET_VAL_BITBLOCK(si_buf_rd, 2, 3);
	stat_reg->bits.acc_pmu_status = BST_GET_VAL_BITBLOCK(si_buf_rd, 4, 5);

	return SNS_DDF_SUCCESS;
}

sns_ddf_sensor_e bmi160_get_reg_fifo_config_1(
		sns_ddf_handle_t                port_handle,
		union bmi160_fifo_config_1      *cfg)
{
	sns_ddf_status_e status;
	uint8_t si_buf;

	cfg->reg = 0;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_FIFO_CONFIG_1,
			&si_buf,
			1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (si_buf & B0_SET)
		cfg->bits.fifo_stop_on_full = 1;

	if (si_buf & B1_SET)
		cfg->bits.fifo_time_en = 1;

	if (si_buf & B2_SET)
		cfg->bits.fifo_tag_int2_en = 1;

	if (si_buf & B3_SET)
		cfg->bits.fifo_tag_int1_en = 1;

	if (si_buf & B4_SET)
		cfg->bits.fifo_header_en = 1;

	if (si_buf & B5_SET)
		cfg->bits.fifo_mag_en = 1;

	if (si_buf & B6_SET)
		cfg->bits.fifo_acc_en = 1;

	if (si_buf & B7_SET)
		cfg->bits.fifo_gyr_en = 1;

	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e bmi160_set_reg_target_page(
		sns_ddf_handle_t        port_handle,
		uint8_t                 page)
{
	sns_ddf_status_e status;
	uint8_t si_buf;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_CMD_EXT_MODE,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	si_buf = BST_SET_VAL_BITBLOCK(si_buf, 4, 5, page);
	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_CMD_EXT_MODE, &si_buf, 1);

	return status;
}

sns_ddf_status_e bmi160_set_reg_acc_range(
		sns_ddf_handle_t        port_handle,
		uint8_t                 range)
{
	sns_ddf_status_e status;
	uint8_t si_buf;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_ACC_RANGE,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	si_buf = BST_SET_VAL_BITBLOCK(si_buf, 0, 3, range);
	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_ACC_RANGE, &si_buf, 1);

	return status;
}

sns_ddf_status_e bmi160_set_reg_gyr_range(
		sns_ddf_handle_t        port_handle,
		uint8_t                 range)
{
	sns_ddf_status_e status;
	uint8_t si_buf;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_GYR_RANGE,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	si_buf = BST_SET_VAL_BITBLOCK(si_buf, 0, 3, range);
	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_GYR_RANGE, &si_buf, 1);

	return status;
}

sns_ddf_status_e bmi160_set_reg_int_en_0(
		sns_ddf_handle_t        port_handle,
		uint8_t                 bit,
		bool                    enable)
{
	sns_ddf_status_e status;
	uint8_t si_buf;

	if (bit > 7) {
		return SNS_DDF_EINVALID_PARAM;
	}

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_INT_EN_0,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (enable) {
		si_buf = BST_SET_VAL_BIT(si_buf, bit);
	} else {
		si_buf = BST_CLR_VAL_BIT(si_buf, bit);
	}

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_INT_EN_0,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e bmi160_set_reg_int_en_1(
		sns_ddf_handle_t        port_handle,
		uint8_t                 bit,
		bool                    enable)
{
	sns_ddf_status_e status;
	uint8_t si_buf;

	if (bit > 6) {
		return SNS_DDF_EINVALID_PARAM;
	}

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_INT_EN_1,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (enable) {
		si_buf = BST_SET_VAL_BIT(si_buf, bit);
	} else {
		si_buf = BST_CLR_VAL_BIT(si_buf, bit);
	}

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_INT_EN_1,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e bmi160_set_reg_int_out_ctrl(
		sns_ddf_handle_t        port_handle,
		uint8_t                 pin_num,
		bool                    enable)
{
	sns_ddf_status_e status;

	uint8_t si_buf;
	uint8_t bit_blk;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_INT_OUT_CTRL,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	bit_blk = enable ? 0x0a : 0x02;
	switch (pin_num) {
		case 1:
			si_buf = BST_SET_VAL_BITBLOCK(si_buf, 0, 3, bit_blk);
			break;
		case 2:
			si_buf = BST_SET_VAL_BITBLOCK(si_buf, 4, 7, bit_blk);
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_INT_OUT_CTRL,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}


sns_ddf_status_e bmi160_set_reg_int_latch(
		void            *plat_obj,
		uint8_t         int_latch_regv)
{
	sns_ddf_status_e status;
	sns_ddf_handle_t port_handle = (sns_ddf_handle_t)plat_obj;
	uint8_t si_buf;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_INT_LATCH, &si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);


	si_buf = BST_SET_VAL_BITBLOCK(si_buf, 0, 3, int_latch_regv);
	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_INT_LATCH,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;

}

sns_ddf_sensor_e bmi160_set_reg_fifo_config_1(
		sns_ddf_handle_t                port_handle,
		union bmi160_fifo_config_1      *cfg)
{
	sns_ddf_sensor_e status;

	uint8_t si_buf_wr = 0;
	uint8_t si_buf_rd = 0;

	if (cfg->bits.fifo_stop_on_full)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 0);

	if (cfg->bits.fifo_time_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 1);

	if (cfg->bits.fifo_tag_int2_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 2);

	if (cfg->bits.fifo_tag_int1_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 3);

	if (cfg->bits.fifo_header_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 4);

	if (cfg->bits.fifo_mag_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 5);

	if (cfg->bits.fifo_acc_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 6);

	if (cfg->bits.fifo_gyr_en)
		si_buf_wr = BST_SET_VAL_BIT(si_buf_wr, 7);

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_FIFO_CONFIG_1,
			&si_buf_rd, 1);

	//the reason to check this is to avoid unnecessary bus traffic
	//and possible impact on FIFO operations
	if (si_buf_rd != si_buf_wr) {
		status = bmi160_sbus_write_wrapper(port_handle,
				BMI160_REGA_USR_FIFO_CONFIG_1,
				&si_buf_wr, 1);
	}

	return status;
}


sns_ddf_status_e bmi160_set_reg_fifo_wml(
		sns_ddf_handle_t        port_handle,
		uint8_t                 wml_reg)
{
	sns_ddf_status_e status;
	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_FIFO_CONFIG_0,
			&wml_reg, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

int32_t bmi160_set_reg_tap_settings(
		void                    *plat_obj,
		bmi160_tap_settings_s   *tap_settings)
{
	uint8_t regv;
	uint32_t err;

	regv = 0;
	err = bmi160_sbus_read_wrapper(plat_obj,
			BMI160_REGA_USR_INT_TAP_0, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = BST_SET_VAL_BITBLOCK(regv, 0, 2, tap_settings->dur);
	regv = BST_SET_VAL_BITBLOCK(regv, 6, 6, tap_settings->shock);
	regv = BST_SET_VAL_BITBLOCK(regv, 7, 7, tap_settings->quiet);

	err = bmi160_sbus_write_wrapper(plat_obj,
			BMI160_REGA_USR_INT_TAP_0, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = bmi160_sbus_read_wrapper(plat_obj,
			BMI160_REGA_USR_INT_TAP_1, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = BST_SET_VAL_BITBLOCK(regv, 0, 4, tap_settings->th);
	err = bmi160_sbus_write_wrapper(plat_obj,
			BMI160_REGA_USR_INT_TAP_1, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	return 0;
}

/*!
 * @brief Find the matched internal ODR for desired ODR.

 *
 * @param[in]  odr_req      New desired ODR.
 * @param[out] idx_odr_matched         The index of matched internal ODR in lis3dsh_odr.
 *
 * @return -1
 *         if no matching odr is found
 */
//reviewed
int32_t bmi160_get_matching_odr_map_idx(sns_ddf_odr_t odr_req)
{
	uint32_t idx;

	for (idx = 0; idx < BST_ARRAY_SIZE(BMI160_REGV_ODR_MAP); idx++) {
		if (odr_req <= BMI160_REGV_ODR_MAP[idx].l)
			return (int32_t)idx;
	}

	return -1;
}

void bmi160_dump_core_reg(sns_ddf_handle_t port_handle)
{
#if BMI160_CONFIG_ENABLE_DBG_MSG
	uint8_t si_buf_rd[16] = "";
	sns_ddf_status_e status;
	uint8_t i;

	status = bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_CHIP_ID,
			si_buf_rd, 4);
	BMI160_MSG_1(HIGH, "[dump_core_reg] dev_ver: %s", SNS_DD_MODULE_VER_BMI160);
	BMI160_MSG_4(HIGH, "[dump_core_reg] @0x00: 0x%02x @0x01: 0x%02x @0x02: 0x%02x @0x03: 0x%02x",
			si_buf_rd[0], si_buf_rd[1], si_buf_rd[2], si_buf_rd[3]);

	status = bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_STATUS,
			si_buf_rd, 1);
	BMI160_MSG_2(HIGH, "[dump_core_reg] %d @0x1b: 0x%02x",
			status, si_buf_rd[0]);

	status = bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_ACC_CONF,
			si_buf_rd, 8);
	for (i = 0; i < 8; i++) {
		BMI160_MSG_3(HIGH, "[dump_core_reg] %d @0x%02x: 0x%02x",
				status, 0x40 + i, si_buf_rd[i]);
	}

	status = bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_INT_EN_0,
			si_buf_rd, 9);
	for (i = 0; i < 9; i++) {
		BMI160_MSG_3(HIGH, "[dump_core_reg] %d @0x%02x: 0x%02x",
				status, 0x50 + i, si_buf_rd[i]);
	}

	BST_IGNORE_WARNING_UNUSED_VAR(status);
#endif
}

#if BMI160_CONFIG_ENABLE_MAG_IF
//<SLAVE_IF_MAG>

void bmi160_slave_udelay(void *bmi160_handle, uint32_t us)
{
	struct bms_platform_data *bps_data =
		(struct bms_platform_data *)bmi160_handle;
	bps_data->udelay(us);
}


int32_t bmi160_slave_i2c_read(
		void            *bmi160_handle,
		uint8_t         slave_reg_addr,
		uint8_t         *buf,
		uint32_t        len)
{
	int32_t err;
	struct bms_platform_data *bps_data =
		(struct bms_platform_data *)bmi160_handle;
	uint8_t regv;
	void *sbus_obj = bps_data->sbus_obj;

	regv = slave_reg_addr;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_USR_MAG_IF_2, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	bps_data->udelay(1 * 1000);
	err = bps_data->bus_read(sbus_obj,
			BMI160_REGA_USR_DATA_0, buf, len < 8 ? len : 8);
	BMI160_DD_CHECK_RETVAL(err, 0);

	return 0;
}

int32_t bmi160_slave_i2c_write_byte(
		void    *bmi160_handle,
		uint8_t slave_reg_addr,
		uint8_t slave_reg_val)
{
	int32_t err;

	struct bms_platform_data *bps_data =
		(struct bms_platform_data *)bmi160_handle;

	void *sbus_obj = bps_data->sbus_obj;

	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_USR_MAG_IF_4, &slave_reg_val, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_USR_MAG_IF_3, &slave_reg_addr, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	return 0;
}

static
int32_t bmi160_sbus_reg_set_bit_blk_val(
		struct bms_platform_data *bps_data,
		uint8_t rega,
		uint8_t bit_start,
		uint8_t bit_end,
		uint8_t val_bit_blk)
{
	int32_t err;
	uint8_t regv = 0;
	void *sbus_obj = bps_data->sbus_obj;

	err = bps_data->bus_read(sbus_obj, rega,
			&regv, 1);

	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = BST_SET_VAL_BITBLOCK(regv, bit_start, bit_end, val_bit_blk);

	err  = bps_data->bus_write(sbus_obj, rega,
			&regv, 1);

	return err;
}

int32_t bmi160_slave_init(
		struct bms_platform_data        *bps_data,
		struct bmi160_slave             *slave_desc,
		uint8_t                         start_auto)
{
	int32_t err;

	uint8_t regv;
	uint8_t regv_mag_if_1;
	uint8_t si_buf_rd[8] = "";

	void *sbus_obj = bps_data->sbus_obj;

	void *bmi160_handle = bps_data;

	regv = BMI160_REGV_CMD_MAG_MODE_NORMAL;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_CMD_CMD, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);
	bps_data->udelay(BMI160_SPEC_MAG_STARTUP_TIME_MS * 1000);

	//set mag to 25HZ
	regv = 0x06;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_USR_MAG_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = BMI160_REGV_CMD_EXT_MODE_EN_B0;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_CMD_CMD, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = BMI160_REGV_CMD_EXT_MODE_EN_B1;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_CMD_CMD, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = BMI160_REGV_CMD_EXT_MODE_EN_B2;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_CMD_CMD, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);


	regv = 0;
	err = bps_data->bus_read(sbus_obj,
			BMI160_REGA_CMD_EXT_MODE, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);
	regv = BST_SET_VAL_BITBLOCK(regv, 4, 5, 1);
	regv = BST_SET_VAL_BIT(regv, 7);
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_CMD_EXT_MODE, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = bmi160_sbus_reg_set_bit_blk_val(bps_data,
			0x05, 4, 5, 3);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = 0;
	regv = BST_SET_VAL_BITBLOCK(regv, 4, 5, 0);
	regv = BST_SET_VAL_BIT(regv, 7);
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_CMD_EXT_MODE, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = bmi160_sbus_reg_set_bit_blk_val(bps_data,
			BMI160_REGA_USR_MAG_IF_0, 1, 7, slave_desc->i2c_addr);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv_mag_if_1 = 0;
	err = bps_data->bus_read(sbus_obj,
			BMI160_REGA_USR_MAG_IF_1, &regv_mag_if_1, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = regv_mag_if_1;
	regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, slave_desc->data_len);
	regv = BST_SET_VAL_BITBLOCK(regv, 2, 5, slave_desc->mag_offset);
	regv = BST_SET_VAL_BIT(regv, 7);
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_USR_MAG_IF_1, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = bmi160_sbus_reg_set_bit_blk_val(bps_data,
			BMI160_REGA_USR_IF_CONF, 4, 5, 2);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = slave_desc->set_power_mode(bmi160_handle, BMI160_SLAVE_POWER_MODE_ON);
	BMI160_DD_CHECK_RETVAL(err, 0);

	regv = slave_desc->reg_addr_chip_id;
	err = bps_data->bus_write(sbus_obj,
			BMI160_REGA_USR_MAG_IF_2, &regv, 1);
	BMI160_DD_CHECK_RETVAL(err, 0);

	bps_data->udelay(1 * 1000);
	regv = 0;
	err = bps_data->bus_read(sbus_obj,
			BMI160_REGA_USR_DATA_0, si_buf_rd, 2);
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = slave_desc->verify_chip_id(si_buf_rd[0] | (si_buf_rd[1] << 8));
	BMI160_DD_CHECK_RETVAL(err, 0);

	err = slave_desc->config_odr(bmi160_handle, slave_desc->odr_max);
	BMI160_DD_CHECK_RETVAL(err, 0);

	if (!slave_desc->slave_inited) {
		if (slave_desc->init_private_data) {
			err = slave_desc->init_private_data(bmi160_handle,
					&slave_desc->private_data_slave);
			if (!err) {
				slave_desc->slave_inited = 1;
			}
		}
	}

	if (start_auto) {
		//NOTE: don't interleave other I2C commands between here and <close_manual_config_of_mag_if>
		err = bps_data->bus_write(sbus_obj,
				BMI160_REGA_USR_MAG_IF_2,
				&slave_desc->reg_addr_data, 1);
		BMI160_DD_CHECK_RETVAL(err, 0);

		err = slave_desc->force_one_measurement(bmi160_handle);
		BMI160_DD_CHECK_RETVAL(err, 0);

		//<close_manual_config_of_mag_if>
		regv = regv_mag_if_1;
		regv = BST_CLR_VAL_BIT(regv, 7);
		err = bps_data->bus_write(sbus_obj,
				BMI160_REGA_USR_MAG_IF_1, &regv, 1);
		BMI160_DD_CHECK_RETVAL(err, 0);
	}

	return 0;
}

int32_t bmi160_slave_deinit(
		struct bms_platform_data    *bps_data,
		struct bmi160_slave         *slave_desc)
{
	//TODO: MAG
	return 0;
}

//</SLAVE_IF_MAG>
#endif  //BMI160_CONFIG_ENABLE_MAG_IF


#if DEBUG
static void cd1__________________________________________________dummy()
{
}
#endif

//reviewed
void sns_dd_bmi160_populate_hw_mod_list(sns_dd_bmi160_state_t   *state)
{
	uint32_t i;
	struct bmi160_hw_mod *hw_mod;

	hw_mod = state->hw_mods + BMI160_HW_MOD_IDX_ACC;
	for (i = 0; i < BST_ARRAY_SIZE(hw_mod->sensor_type_supported); i++) {
		hw_mod->sensor_type_supported[i] = -1;
	}
	hw_mod->name                    = "HWM_ACC";
	hw_mod->hw_mod_type = BMI160_HW_MOD_TYPE_ACC;
	hw_mod->sensor_type_supported[0] = SNS_DDF_SENSOR_ACCEL;
	hw_mod->sensor_type_supported[1] = SNS_DDF_SENSOR_DOUBLETAP;
	hw_mod->sensor_type_supported[2] = SNS_DDF_SENSOR_TEMP;
	hw_mod->set_power_state         = sns_dd_bmi160_hw_mod_acc_set_power_state;
	hw_mod->get_best_match_odr      = sns_dd_bmi160_hw_mod_acc_get_best_match_odr;
	hw_mod->set_odr                 = sns_dd_bmi160_hw_mod_acc_set_odr;
	hw_mod->set_range               = sns_dd_bmi160_hw_mod_acc_set_range;
	hw_mod->dev_inst                = state;

	hw_mod = state->hw_mods + BMI160_HW_MOD_IDX_GYR;
	for (i = 0; i < BST_ARRAY_SIZE(hw_mod->sensor_type_supported); i++) {
		hw_mod->sensor_type_supported[i] = -1;
	}
	hw_mod->name                    = "HWM_GYR";
	hw_mod->hw_mod_type = BMI160_HW_MOD_TYPE_GYR;
	hw_mod->sensor_type_supported[0] = SNS_DDF_SENSOR_GYRO;
	//hw_mod->sensor_type_supported[1] = SNS_DDF_SENSOR_TEMP;
	hw_mod->set_power_state         = sns_dd_bmi160_hw_mod_gyr_set_power_state;
	hw_mod->get_best_match_odr      = sns_dd_bmi160_hw_mod_gyr_get_best_match_odr;
	hw_mod->set_odr                 = sns_dd_bmi160_hw_mod_gyr_set_odr;
	hw_mod->set_range               = sns_dd_bmi160_hw_mod_gyr_set_range;
	hw_mod->dev_inst                = state;

	hw_mod = state->hw_mods + BMI160_HW_MOD_IDX_MAG;
	for (i = 0; i < BST_ARRAY_SIZE(hw_mod->sensor_type_supported); i++) {
		hw_mod->sensor_type_supported[i] = -1;
	}

	hw_mod->name                            = "HWM_MAG";
	hw_mod->hw_mod_type                     = BMI160_HW_MOD_TYPE_MAG;
#if BMI160_CONFIG_ENABLE_MAG_IF
	hw_mod->sensor_type_supported[0]        = SNS_DDF_SENSOR_MAG;

	hw_mod->set_power_state                 = sns_dd_bmi160_hw_mod_mag_set_power_state,
	hw_mod->get_best_match_odr              = sns_dd_bmi160_hw_mod_mag_get_best_match_odr,
	hw_mod->set_odr                         = sns_dd_bmi160_hw_mod_mag_set_odr,
	hw_mod->set_range                       = NULL,

	hw_mod->dev_inst                        = state;
#endif

}

//reviewed
uint32_t sns_dd_bmi160_fill_sub_dev_slot(
		sns_dd_bmi160_state_t   *state,
		bmi160_sub_dev_t        *sub_dev_slot,
		sns_ddf_handle_t        smgr_handle,
		uint32_t                gpio,
		uint32_t                num_sensors,
		sns_ddf_sensor_e        sensors[],
		sns_ddf_sensor_e        *sensors_init[])
{
	uint32_t num_sensors_filled = 0;
	uint32_t i;

	if ((NULL == state) || (NULL == sub_dev_slot) || (NULL == sensors_init))
		return 0;

	//CHECK: should fill at least some sensors
	if (num_sensors > BMI160_MAX_SENSORS_NUM) {
		BMI160_MSG_0(ERROR, "too many sensors for the subdev slot");
		return 0;
	}

	for (i = 0; i < num_sensors; i++) {
		if ((sensors[i] == SNS_DDF_SENSOR_ACCEL)
				|| (sensors[i] == SNS_DDF_SENSOR_TEMP)
				|| (sensors[i] == SNS_DDF_SENSOR_DOUBLETAP)
				|| (sensors[i] == SNS_DDF_SENSOR_GYRO)
#if BMI160_CONFIG_ENABLE_MAG_IF
				|| (sensors[i] == SNS_DDF_SENSOR_MAG)
#endif
		   ) {
			sub_dev_slot->sensors[num_sensors_filled].sensor_type
				= sensors[i];

			num_sensors_filled++;
			(*sensors_init)[i] = sensors[i];
		}
	}

	sub_dev_slot->smgr_handle   = smgr_handle;
	sub_dev_slot->num_sensors   = num_sensors_filled;
	sub_dev_slot->private_data  = state;

	return sub_dev_slot->num_sensors;
}

//reviewed
static sns_dd_bmi160_state_t* sns_dd_bmi160_find_same_dev(
		sns_ddf_port_config_s   *port_config,
		sns_ddf_sensor_e        *sensors,
		uint8_t                 num_sensors)
{
	bool mag_req;
	int8_t i;
	sns_dd_bmi160_state_t *dev = NULL;

	dev = (sns_dd_bmi160_state_t*)bmi160_sns_dd_list_head.next;

	mag_req = false;
	for (i = 0; i < num_sensors; i++) {
		if (SNS_DDF_SENSOR_MAG == sensors[i]) {
			mag_req = true;
			break;
		}
	}

	if (mag_req) {
#if BMI160_CONFIG_ENABLE_MAG_IF
	//TODO: MAG
	//we don't have a good way to way which mag slave belongs to which BMI160 master yet
	//thus we just return the first instance of the device
	return dev;
#else
	return NULL;
#endif
	}


	while (NULL != dev) {
		if (sns_ddf_is_same_port_id(port_config, &dev->port_id)) {
			return dev;
		} else {
			dev = dev->next;
		}
	}
	return NULL;
}

//TODO: static
void sns_dd_bmi160_reckon_ts_host_from_dev(
		sns_dd_bmi160_state_t   *state,
		uint32_t                ts_dev,
		sns_ddf_time_t          *ts_sys)
{
	*ts_sys = state->ts_sync_sys_and_dev.ts_sys +
		BMI160_SSC_US_2_TICKS(bmi160_get_time_elapse_dev_us(state->ts_sync_sys_and_dev.ts_dev, ts_dev));

	BMI160_MSG_4(HIGH, "[reckon_ts_host] <%d 0x%x> <%d 0x%x>",
			state->ts_sync_sys_and_dev.ts_sys,
			state->ts_sync_sys_and_dev.ts_dev,
			*ts_sys, ts_dev);
}

//TODO: handle the error in a graceful way
sns_ddf_status_e sns_dd_bmi160_handle_device_err(
		sns_dd_bmi160_state_t           *state,
		union bmi160_hw_err_stat        *hw_err_st)
{
	sns_ddf_status_e status;

	BMI160_MSG_3(ERROR, "[handle_dev_err] 0x%02x fatal_err: %d drop_cmd_err: %d",
			hw_err_st->regv,
			hw_err_st->bits.fatal_err,
			hw_err_st->bits.drop_cmd_err);

	if (hw_err_st->bits.fatal_err) {
		status = sns_dd_bmi160_soft_reset_and_cfg_default(state);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	}

	return SNS_DDF_SUCCESS;
}


//reviewed
sns_ddf_status_e sns_dd_bmi160_signal_register(
		sns_dd_bmi160_state_t   *state)
{
	sns_ddf_status_e status;
	uint32_t irq_trigger_type       = BMI160_CONFIG_IRQ_TRIGGER_TYPE_DFT;
	bool signal_registered;

	signal_registered = state->signal_registered;
#if BMI160_CONFIG_WMI_IRQ_TRIGGER_TYPE_LVL
	if (state->int_en_flags.bits.fifo.flag) {
		irq_trigger_type = SNS_DDF_SIGNAL_IRQ_HIGH;
	}

	if (signal_registered
			&& state->int_en_flags.bits.fifo.flag
			&& (SNS_DDF_SIGNAL_IRQ_HIGH != state->irq_trigger_type)) {
		/* need to change trigger type */
		status = sns_ddf_signal_deregister(state->gpio1);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		signal_registered = false;
		state->signal_registered = false;
	}
#endif
	if (!signal_registered) {
		status = bmi160_set_reg_int_out_ctrl(state->port_handle, 1, true);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		status = sns_ddf_signal_register(
				state->gpio1,
				state,
				&SNS_DD_IF_BMI160,
				irq_trigger_type);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		state->signal_registered = true;
		state->irq_trigger_type = irq_trigger_type;
	}

	return SNS_DDF_SUCCESS;
}

//reviewed
sns_ddf_status_e sns_dd_bmi160_signal_deregister(
		sns_dd_bmi160_state_t *state)
{
	sns_ddf_status_e status;
	uint32_t signal_needed = 0;

	signal_needed = (state->int_en_flags.flag);

	if (state->signal_registered && (!signal_needed)) {
		status = sns_ddf_signal_deregister(state->gpio1);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		state->signal_registered = false;

		status = bmi160_set_reg_int_out_ctrl(state->port_handle, 1, false);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	}

	return SNS_DDF_SUCCESS;
}


//reviewing
static sns_ddf_status_e sns_dd_bmi160_cfg_int_doubletap(
		sns_dd_bmi160_state_t *state,
		bool enable)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	uint8_t range_idx_acc = state->range_idx_acc;
	bmi160_tap_settings_s tap_settings;
	if (enable) {
		tap_settings = state->tap_settings;
		tap_settings.th = tap_settings.th >> range_idx_acc;
		status = bmi160_set_reg_tap_settings(state->port_handle,
				&tap_settings);
		BMI160_DD_CHECK_RETVAL(status, 0);

		status = bmi160_set_reg_int_en_0(
				state->port_handle,
				BMI160_INT_EN_0_BIT_D_TAP, true);
		BMI160_DD_CHECK_RETVAL(status, 0);
		status = bmi160_set_reg_int_map(
				state->port_handle,
				BMI160_INT_MAP_REG_NUM0,
				BMI160_INT_MAP_0_BIT_D_TAP, true);
		BMI160_DD_CHECK_RETVAL(status, 0);

		status = bmi160_set_reg_int_latch(
				state->port_handle,
				BMI160_CONFIG_INT_LATCH_DT_REGV);
		BMI160_DD_CHECK_RETVAL(status, 0);

		status = sns_dd_bmi160_signal_register(state);
		BMI160_DD_CHECK_RETVAL(status, 0);

		state->int_en_flags.bits.dt = true;
	} else {
		status = bmi160_set_reg_int_en_0(
				state->port_handle,
				BMI160_INT_EN_0_BIT_D_TAP, false);
		status = bmi160_set_reg_int_map(
				state->port_handle,
				BMI160_INT_MAP_REG_NUM0,
				BMI160_INT_MAP_0_BIT_D_TAP, false);
		BMI160_DD_CHECK_RETVAL(status, 0);

		status = bmi160_set_reg_int_latch(
				state->port_handle,
				0);

		BMI160_DD_CHECK_RETVAL(status, 0);

		state->int_en_flags.bits.dt = false;
		status = sns_dd_bmi160_signal_deregister(state);
	}

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}


/*!
 *  @brief Configure (enable/disable) the motion interrupt
 *
 *  @detail
 *  @param[in] state: Ptr to the driver structure
 *  @param[in] enable: If true enable the interrupt if false disable the
 *  interrupt
 *
 *  @return
 *   The error code definition within the DDF
 *   SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
//reviewing
static sns_ddf_status_e sns_dd_bmi160_cfg_int_md(
		sns_dd_bmi160_state_t  *state,
		bool                   enable)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	uint8_t si_buf;

	/*! Perform read, modify & write to set motion interrupt bit */
	status = bmi160_sbus_read_wrapper(state->port_handle,
			BMI160_REGA_USR_INT_EN_0,
			&si_buf,
			1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (enable) {
		/*! enable XYZ slope interrupt */
		si_buf = BST_SET_VAL_BIT(si_buf, 0);
		si_buf = BST_SET_VAL_BIT(si_buf, 1);
		si_buf = BST_SET_VAL_BIT(si_buf, 2);

	} else {
		si_buf = BST_CLR_VAL_BIT(si_buf, 0);
		si_buf = BST_CLR_VAL_BIT(si_buf, 1);
		si_buf = BST_CLR_VAL_BIT(si_buf, 2);
	}

	status = bmi160_sbus_write_wrapper(state->port_handle,
			BMI160_REGA_USR_INT_EN_0,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	status = bmi160_set_reg_int_map(
			state->port_handle, BMI160_INT_MAP_REG_NUM0,
			BMI160_INT_MAP_0_BIT_ANYM, enable);

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);


	return SNS_DDF_SUCCESS;;
}

#if BMI160_CONFIG_ENABLE_MD
//reviewing
static sns_ddf_status_e sns_dd_bmi160_cfg_md_dur(
		sns_dd_bmi160_state_t *state)
{
	uint8_t si_buf_wr;

	si_buf_wr = 0;
	si_buf_wr = BST_SET_VAL_BITBLOCK(si_buf_wr, 0, 1, BMI160_CONFIG_MD_DUR);

	return bmi160_sbus_write_wrapper(state->port_handle,
			BMI160_REGA_USR_INT_MOTION_0,
			&si_buf_wr, 1);
}

/*!
 *  @brief Configure the motion interrupt threshold
 *
 *  @detail
 *  Programs the register BMI160_SLOPE_THRES_REG for the MD
 *  threshold
 *
 *  @param[in] state: Ptr to the driver structure
 *
 *  @return
 *  The error code definition within the DDF
 *  SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
//reviewing
static sns_ddf_status_e sns_dd_bmi160_cfg_md_thresh(
		sns_dd_bmi160_state_t *state)
{
	uint8_t si_buf_wr;

	si_buf_wr = BMI160_CONFIG_MD_THRESHOLD >> state->range_idx_acc;

	return bmi160_sbus_write_wrapper(state->port_handle,
			BMI160_REGA_USR_INT_MOTION_1,
			&si_buf_wr, 1);
}
#endif

//reviewing
static sns_ddf_status_e sns_dd_bmi160_cfg_int_fifo_wml(
		sns_dd_bmi160_state_t *state,
		bool enable)
{
	sns_ddf_status_e status;

	status = bmi160_set_reg_int_en_1(
			state->port_handle,
			BMI160_INT_EN_1_BIT_FF_WML, enable);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	status = bmi160_set_reg_int_map(
			state->port_handle, BMI160_INT_MAP_REG_NUM1,
			BMI160_INT_MAP_1_BIT_WML, enable);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

/*!
 *  @brief Configure (enable/disable) the data ready interrupt
 *
 *  @detail
 *  @param[in] state: Ptr to the driver structure
 *  @param[in] enable: If true enable the interrupt if false disable the
 *  interrupt
 *
 *  @return
 *   The error code definition within the DDF
 *   SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
//reviewed
static sns_ddf_status_e sns_dd_bmi160_cfg_int_drdy(
		sns_dd_bmi160_state_t  *state,
		bool                   enable)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;


	status = bmi160_set_reg_int_en_1(
			state->port_handle,
			BMI160_INT_EN_1_BIT_DRDY, enable);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	status = bmi160_set_reg_int_map(
			state->port_handle, BMI160_INT_MAP_REG_NUM1,
			BMI160_INT_MAP_1_BIT_DRDY, enable);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return status;
}

sns_ddf_status_e sns_dd_bmi160_set_int_drdy_flag(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		bool                    enable)
{
	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			state->int_en_flags.bits.drdy.bits.acc = enable;
			break;
		case SNS_DDF_SENSOR_GYRO:
			state->int_en_flags.bits.drdy.bits.gyr = enable;
			break;
		case SNS_DDF_SENSOR_MAG:
			state->int_en_flags.bits.drdy.bits.mag = enable;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_bmi160_set_int_fifo_flag(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		bool                    enable)
{
	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			state->int_en_flags.bits.fifo.bits.acc = enable;
			break;
		case SNS_DDF_SENSOR_GYRO:
			state->int_en_flags.bits.fifo.bits.gyr = enable;
			break;
		case SNS_DDF_SENSOR_MAG:
			state->int_en_flags.bits.fifo.bits.mag = enable;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	return SNS_DDF_SUCCESS;
}

/*!
 *  @brief Sets the BOSCH BMI160 to its default operational state
 *
 *  @detail
 *  Programs the register BMI160_ACCEL_CTRL5_REG_ADDR for the MD
 *  threshold
 *
 *  @param[in] state: Ptr to the driver structure
 *
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */

//reviewing
static sns_ddf_status_e sns_dd_bmi160_soft_reset_and_cfg_default(
		sns_dd_bmi160_state_t *state)
{
	sns_ddf_status_e status;
	uint8_t  si_buf_wr;
	bmi160_hw_mod_t    *hw_mod;


	state->last_cmd_regv = BMI160_REGV_CMD_NOOP;
	state->hw_err_st.regv = 0;
	/*! soft reset */
	si_buf_wr = BMI160_REGV_CMD_SOFT_RESET;
	status = bmi160_sbus_write_wrapper(state->port_handle,
			BMI160_REGA_CMD_CMD,
			&si_buf_wr, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	sns_ddf_delay(1000 * BMI160_SPEC_STARTUP_TIME_MS);

	INSERT_TRACE_POINT(bmi160, 0x61);

	//set the idx to POR values
	state->range_idx_acc = 1;   /* 1 for +/- 4G */
	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
	if (hw_mod) {
		status = hw_mod->set_range(hw_mod, state->port_handle, state->range_idx_acc);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		sns_ddf_delay(1000 * BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);

		hw_mod->odr_curr = 0;
		status = bmi160_get_curr_odr_map_idx(
				state->port_handle, SNS_DDF_SENSOR_ACCEL, &hw_mod->odr_map_idx);
		sns_ddf_delay(1000 * BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);
	}

	state->range_idx_gyr = BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST) - 1; /* 0 for +/- 2000DPS */
	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
	if (hw_mod) {
		status = hw_mod->set_range(hw_mod, state->port_handle, state->range_idx_gyr);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		sns_ddf_delay(1000 * BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);

		hw_mod->odr_curr = 0;
		status = bmi160_get_curr_odr_map_idx(
				state->port_handle, SNS_DDF_SENSOR_GYRO, &hw_mod->odr_map_idx);
		sns_ddf_delay(1000 * BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);
	}

	/*! usr data config page*/
	status = bmi160_set_reg_target_page(state->port_handle, BMI160_REGV_CMD_TGT_PAGE_USR);
	BMI160_DD_CHECK_RETVAL(status, 0);
	sns_ddf_delay(1000 * BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);


	INSERT_TRACE_POINT(bmi160, 0x6f);
	return status;
}

sns_ddf_status_e sns_dd_bmi160_reset_state(
		sns_dd_bmi160_state_t           *state,
		sns_ddf_sensor_e                sensor_type,
		int32_t                         caller)

{
	sns_ddf_status_e status;
	bmi160_hw_mod_t *hw_mod;
	int32_t idx = -1;
	bmi160_pmu_stat_reg_t   pmu_stat_reg;
	bmi160_status_reg_t     stat_reg;
	uint8_t                 regv;


	BMI160_MSG_2(HIGH, "55555560 - <bmi160_reset_state> sensor_type: %d caller: %d",
			sensor_type, caller);

	bmi160_sbus_read_wrapper(state->port_handle,
			BMI160_REGA_USR_STATUS, &regv, 1);
	bmi160_parse_reg_status(regv, &stat_reg);

	bmi160_get_reg_pmu_status(state->port_handle, &pmu_stat_reg);

	hw_mod = sns_dd_bmi160_get_hw_mod(state, sensor_type);
	if (hw_mod) {
		hw_mod->ref_cnt = 0;
		hw_mod->odr_curr = 0;
	}

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			state->odr_acc_req = 0;
			break;
		case SNS_DDF_SENSOR_TEMP:
			state->odr_tem_req = 0;
			break;
		case SNS_DDF_SENSOR_DOUBLETAP:
			state->odr_dbt_req = 0;
			break;
		case SNS_DDF_SENSOR_GYRO:
			state->odr_gyr_req = 0;
			break;
		case SNS_DDF_SENSOR_MAG:
			state->odr_mag_req = 0;
			break;
		default:
			;
	}

	if (BMI160_REGV_PMU_STAT_ACC_NORMAL != pmu_stat_reg.bits.acc_pmu_status) {
		state->int_en_flags.bits.drdy.bits.acc = false;
		state->int_en_flags.bits.fifo.bits.acc = false;

		state->int_en_flags.bits.dt = false;
		state->int_en_flags.bits.md = false;
	}

	if (BMI160_REGV_PMU_STAT_GYR_NORMAL != pmu_stat_reg.bits.gyr_pmu_status) {
		state->int_en_flags.bits.drdy.bits.gyr = false;
		state->int_en_flags.bits.fifo.bits.gyr = false;
	}

	if (BMI160_REGV_PMU_STAT_MAG_NORMAL != pmu_stat_reg.bits.mag_pmu_status) {
		state->int_en_flags.bits.drdy.bits.mag = false;
		state->int_en_flags.bits.fifo.bits.mag = false;
	}

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			status = bmi160_acc_get_range_idx(state->port_handle, &idx);
			if ((SNS_DDF_SUCCESS != status) || (-1 == idx)) {
				idx = 0;
			}
			state->range_idx_acc = idx;

			hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
			if (hw_mod) {
				status = bmi160_get_curr_odr_map_idx(state->port_handle,
						sensor_type, &idx);

				//ODR register value will be kept when the sensor is in SUSPEND mode
				hw_mod->odr_map_idx = idx;
			}
			break;
		case SNS_DDF_SENSOR_GYRO:
			status = bmi160_gyr_get_range_idx(state->port_handle, &idx);
			if ((SNS_DDF_SUCCESS != status) || (-1 == idx)) {
				idx = BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST) - 1;
			}
			state->range_idx_gyr = idx;

			hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
			if (hw_mod) {
				status = bmi160_get_curr_odr_map_idx(state->port_handle,
						sensor_type, &idx);

				hw_mod->odr_map_idx = idx;
			}
			break;
		case SNS_DDF_SENSOR_MAG:
#if BMI160_CONFIG_ENABLE_MAG_IF
			hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_MAG);
			if (hw_mod) {
				status = bmi160_get_curr_odr_map_idx(state->port_handle,
						sensor_type, &idx);

				hw_mod->odr_map_idx = idx;
			}
#endif
			break;
		default:
			break;
	}

	BMI160_MSG_4(HIGH, "[reset_state] <0x%02x 0x%02x %d %d",
			stat_reg.reg,
			pmu_stat_reg.reg,
			state->range_idx_acc,
			state->range_idx_gyr);

	return SNS_DDF_SUCCESS;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_set_range(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 range_idx)
{
	sns_ddf_status_e status;

	/*! set acc range  */
	status = bmi160_set_reg_acc_range(port_handle, BMI160_ACC_RANGE_REGV_LIST[range_idx]);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return status;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_set_power_state(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		sns_ddf_powerstate_e    power_state)
{
	sns_ddf_status_e status;
	uint8_t regv;
	sns_dd_bmi160_state_t   *state = (sns_dd_bmi160_state_t *)hw_mod->dev_inst;

	switch (power_state) {
		case SNS_DDF_POWERSTATE_LOWPOWER:
			regv = BMI160_REGV_CMD_ACC_MODE_SUSP;
			break;
		default:
			regv = BMI160_REGV_CMD_ACC_MODE_NORMAL;
			break;
	}

	if (!state->int_en_flags.bits.md) {
		status = sns_dd_bmi160_send_cmd(state, regv);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		if (SNS_DDF_POWERSTATE_LOWPOWER != power_state) {
			sns_ddf_delay(BMI160_SPEC_ACC_STARTUP_TIME_MS * 1000);
		}

		if (SNS_DDF_POWERSTATE_LOWPOWER == power_state) {
			hw_mod->odr_curr = 0;
		}
	}

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_PMU_STATUS, &regv, 1);
	BMI160_MSG_1(HIGH, "regv_pmu_stat: 0x%02x", regv);

	return SNS_DDF_SUCCESS;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_get_best_match_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                odr_req,
		sns_ddf_odr_t           *odr_matched)
{
	uint32_t                odr_req_arbitrated = 0;
	sns_dd_bmi160_state_t   *state = (sns_dd_bmi160_state_t *)hw_mod->dev_inst;

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			state->odr_acc_req = odr_req;
			break;
		case SNS_DDF_SENSOR_DOUBLETAP:
			state->odr_dbt_req = odr_req;
			break;
		case SNS_DDF_SENSOR_TEMP:
			state->odr_tem_req = odr_req;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	if (state->odr_dbt_req > 0) {
		odr_req_arbitrated = 200;
	}

	if (odr_req_arbitrated < state->odr_dbt_req) {
		odr_req_arbitrated = state->odr_dbt_req;
	}

	if (odr_req_arbitrated < state->odr_acc_req) {
		odr_req_arbitrated = state->odr_acc_req;
	}

	*odr_matched = odr_req_arbitrated;

	return SNS_DDF_SUCCESS;
}

//reviewed
sns_ddf_status_e sns_dd_bmi160_hw_mod_acc_set_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 odr_regv)
{
	sns_ddf_status_e status;
	uint8_t regv;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_ACC_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	regv = BST_SET_VAL_BITBLOCK(regv, 0, 3, odr_regv);
	regv = BST_SET_VAL_BITBLOCK(regv, 4, 6, BMI160_CONFIG_ACC_BWP);

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_ACC_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	hw_mod->odr_regv = odr_regv;

#if 0//TODO: CHECK the time_to_data with PE
	for (i = 0; i < BST_ARRAY_SIZE(BMI160_REGV_ODR_MAP); i++) {
		if (BMI160_REGV_ODR_MAP[i].r == state->acc_bw) {
			/* Set the is_data_valid flag to false so the driver will know
			 * to flag all output as invalid until the timer expires */

			// If there is currently a bw-timer set, cancel it before starting a new one
			if (state->bw_timer_pending)
			{
				DDF_MSG_0(HIGH, "BMI160 - BW timer already running, cancelling it...");
				if ((status = sns_ddf_timer_cancel(state->bw_timer)) != SNS_DDF_SUCCESS)
				{
					DDF_MSG_1(ERROR, "BMI160 - BW timer cancel FAILED. Error %d", status);
					return status;
				}
			}

			/* Set a timer here for BMI160_ACC_BW_DELAY_TIME[BW_index] * (BMI160_BW_FILTER_SIZE - 1)
			 * This will invalidate the next (BMI160_BW_FILTER_SIZE - 1) potentially unstable samples from
			 * this sensor. The next (BMI160_BW_FILTER_SIZE-th) sample should be stable since the internal
			 * filter on the BMI160 sensor is guaranteed to use valid values, at that point.
			 */
			if ((status = sns_ddf_timer_start(state->bw_timer,
							BMI160_ACC_BW_DELAY_TIME[i]
							* (BMI160_BW_FILTER_SIZE - 1)))
					== SNS_DDF_SUCCESS)
			{
				state->bw_timer_pending = true;
				DDF_MSG_1(MEDIUM, "BMI160 - Started BW timer for %u us",
						BMI160_ACC_BW_DELAY_TIME[i]
						* (BMI160_BW_FILTER_SIZE - 1));
			}
			else
			{
				DDF_MSG_1(ERROR, "BMI160 - BW timer failed to start. Error: %d", status);
				return status;
			}

			break;
		}
	}
#endif

	return SNS_DDF_SUCCESS;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_set_range(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 range_idx)
{
	sns_ddf_status_e status;

	/*! set gyr range  */
	status = bmi160_set_reg_gyr_range(port_handle, BMI160_GYR_RANGE_REGV_LIST[range_idx]);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_set_power_state(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		sns_ddf_powerstate_e    power_state)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	uint8_t regv;
	sns_dd_bmi160_state_t   *state = (sns_dd_bmi160_state_t *)hw_mod->dev_inst;

	switch (power_state) {
		case SNS_DDF_POWERSTATE_LOWPOWER:
			regv = BMI160_REGV_CMD_GYR_MODE_SUSP;
			break;
		default:
			regv = BMI160_REGV_CMD_GYR_MODE_NORMAL;
			break;
	}

	status = sns_dd_bmi160_send_cmd(state, regv);

	if (SNS_DDF_POWERSTATE_LOWPOWER != power_state) {
		sns_ddf_delay(BMI160_SPEC_GYR_STARTUP_TIME_MS * 1000);
	}

	if (SNS_DDF_POWERSTATE_LOWPOWER == power_state) {
		hw_mod->odr_curr = 0;
	}

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_PMU_STATUS, &regv, 1);
	BMI160_MSG_1(HIGH, "regv_pmu_stat: 0x%02x", regv);

	return status;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_get_best_match_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                odr_req,
		sns_ddf_odr_t           *odr_matched)
{
	uint32_t                odr_req_arbitrated = 0;
	sns_dd_bmi160_state_t   *state = (sns_dd_bmi160_state_t *)hw_mod->dev_inst;

	switch (sensor_type) {
		case SNS_DDF_SENSOR_GYRO:
			state->odr_gyr_req = odr_req;
			break;
		case SNS_DDF_SENSOR_TEMP:
			state->odr_tem_req = odr_req;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	if (odr_req_arbitrated < state->odr_gyr_req) {
		odr_req_arbitrated = state->odr_gyr_req;
	}

	*odr_matched = odr_req_arbitrated;

	return SNS_DDF_SUCCESS;
}

//reviewed
sns_ddf_status_e sns_dd_bmi160_hw_mod_gyr_set_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 odr_regv)
{
	sns_ddf_status_e status;
	uint8_t regv;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_GYR_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	regv = BST_SET_VAL_BITBLOCK(regv, 0, 3, odr_regv);
	regv = BST_SET_VAL_BITBLOCK(regv, 4, 5, BMI160_CONFIG_GYR_BWP);

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_GYR_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	hw_mod->odr_regv = odr_regv;

	return SNS_DDF_SUCCESS;
}

//reviewed
#if BMI160_CONFIG_ENABLE_MAG_IF
//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_mag_set_power_state(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		sns_ddf_powerstate_e    power_state)
{
	sns_ddf_status_e        status = SNS_DDF_SUCCESS;
	sns_dd_bmi160_state_t   *state = (sns_dd_bmi160_state_t *)hw_mod->dev_inst;
	uint8_t                 regv;
	struct bms_platform_data *bps_data = &state->bps_data;

	switch (power_state) {
		case SNS_DDF_POWERSTATE_LOWPOWER:
			regv = BMI160_REGV_CMD_MAG_MODE_SUSP;
			break;
		default:
			regv = BMI160_REGV_CMD_MAG_MODE_NORMAL;
			break;
	}

	if (SNS_DDF_POWERSTATE_LOWPOWER != power_state) {
		status = bmi160_slave_init(bps_data, state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG], true);
	} else {
		status = bmi160_slave_deinit(bps_data, state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG]);
		hw_mod->odr_curr = 0;
	}
	BMI160_DD_CHECK_RETVAL(status, 0);

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_PMU_STATUS, &regv, 1);
	BMI160_MSG_1(HIGH, "regv_pmu_stat: 0x%02x", regv);


	return status;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_hw_mod_mag_get_best_match_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                odr_req,
		sns_ddf_odr_t           *odr_matched)
{
	uint32_t                odr_req_arbitrated = 0;
	sns_dd_bmi160_state_t   *state = (sns_dd_bmi160_state_t *)hw_mod->dev_inst;

	switch (sensor_type) {
		case SNS_DDF_SENSOR_MAG:
			state->odr_mag_req = odr_req;
			break;
		case SNS_DDF_SENSOR_TEMP:
			state->odr_tem_req = odr_req;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	if (odr_req_arbitrated < state->odr_mag_req) {
		odr_req_arbitrated = state->odr_mag_req;
	}

	*odr_matched = odr_req_arbitrated;

	return SNS_DDF_SUCCESS;
}

//reviewed
sns_ddf_status_e sns_dd_bmi160_hw_mod_mag_set_odr(
		struct bmi160_hw_mod    *hw_mod,
		sns_ddf_handle_t        port_handle,
		uint8_t                 odr_regv)
{
	sns_ddf_status_e        status;
	uint8_t                 regv;

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_MAG_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	regv = BST_SET_VAL_BITBLOCK(regv, 0, 3, odr_regv);

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_USR_MAG_CONF, &regv, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	hw_mod->odr_regv = odr_regv;

	return SNS_DDF_SUCCESS;
}

#endif  //BMI160_CONFIG_ENABLE_MAG_IF

void sns_dd_bmi160_update_hw_mod_odr_max(
		sns_dd_bmi160_state_t   *state)
{
	bmi160_hw_mod_t         *hw_mod;
	bmi160_hw_mod_t         *hw_mod_odr_max = NULL;
	uint32_t                odr_max = 0;

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)) {
		if (hw_mod->odr_curr >= odr_max) {
			hw_mod_odr_max = hw_mod;
			odr_max = hw_mod->odr_curr;
		}
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)) {
		if (hw_mod->odr_curr >= odr_max) {
			hw_mod_odr_max = hw_mod;
			odr_max = hw_mod->odr_curr;
		}
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_MAG);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)) {
		if (hw_mod->odr_curr >= odr_max) {
			hw_mod_odr_max = hw_mod;
			odr_max = hw_mod->odr_curr;
		}
	}

	BMI160_MSG_1(HIGH,
			"hw_mod_odr_max: %d",
			(NULL != hw_mod_odr_max) ? hw_mod_odr_max->hw_mod_type : NULL);

	state->hw_mod_odr_max = hw_mod_odr_max;


}

bmi160_hw_mod_t * sns_dd_bmi160_fifo_get_master(
		sns_dd_bmi160_state_t   *state)
{
	bmi160_hw_mod_t         *hw_mod;
	bmi160_hw_mod_t         *hw_mod_fifo_master = NULL;
	uint16_t                odr_max = 0;
	uint16_t                odr_curr = 0;

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_acc > 0)) {
		odr_curr = hw_mod->odr_curr;

		if (odr_curr > odr_max) {
			odr_max = odr_curr;
			hw_mod_fifo_master = hw_mod;
		}
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_gyr > 0)) {
		odr_curr = hw_mod->odr_curr;

		//note the "=", we want gyro to be the master when possible
		if (odr_curr >= odr_max) {
			odr_max = odr_curr;
			hw_mod_fifo_master = hw_mod;
		}
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_MAG);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_mag > 0)) {
		odr_curr = hw_mod->odr_curr;

		if (odr_curr > odr_max) {
			odr_max = odr_curr;
			hw_mod_fifo_master = hw_mod;
		}
	}


	return hw_mod_fifo_master;
}

static void sns_dd_bmi160_fifo_reset_state(sns_dd_bmi160_state_t *state)
{
	bmi160_hw_mod_t *hw_mod_fifo_master;

	state->ff_sample_sync_info.avail_master_itvl_est        = 0;

	state->ff_sample_sync_info.fc_master                    = 0;
	state->ff_sample_sync_info.fc_master_last_sync_ref      = 0;
	state->ff_sample_sync_info.ts_sys_last_sync_ref         = 0;

	state->ff_1st_read                                      = 1;

	hw_mod_fifo_master = sns_dd_bmi160_fifo_get_master(state);
	if (NULL != hw_mod_fifo_master) {
		state->hw_mod_ff_master = hw_mod_fifo_master;

		state->ff_sample_sync_info.ts_itvl_master_sample_exp    =
			BMI160_SSC_US_2_TICKS(1e6 / hw_mod_fifo_master->odr_curr);
		state->ff_sample_sync_info.ts_itvl_master_sample_est    =
			state->ff_sample_sync_info.ts_itvl_master_sample_exp;

		if ((1000 / hw_mod_fifo_master->odr_curr) <= 10) {
			state->ff_wmi_missing_possible = 1;
		} else {
			state->ff_wmi_missing_possible = 0;
		}
	} else {
		state->hw_mod_ff_master = NULL;

		state->ff_sample_sync_info.ts_itvl_master_sample_exp    =
			(sns_ddf_time_t)(-1);
	}

	BMI160_MSG_2(HIGH,
			"[fifo_reset_state] <ff_master: %d master_odr: %d>",
			hw_mod_fifo_master ? hw_mod_fifo_master->hw_mod_type : -1,
			hw_mod_fifo_master ? hw_mod_fifo_master->odr_curr : 0);
}

/*!
 * @brief caculate  the shared fifo watermark level for interrupt by provide a single sensor type.

 *
 * @param[in]  odr_req      New desired ODR.
 * @param[out] odr_matched          Matched internal ODR.
 * @param[out] idx_odr_matched         The index of matched internal ODR in lis3dsh_odr.
 *
 * @return SNS_DDF_SUCCESS if this operation was done successfully. Otherwise
 *         SNS_DDF_EDEVICE, SNS_DDF_EBUS, SNS_DDF_EINVALID_PARAM, or SNS_DDF_EFAIL to
 *         indicate and error has occurred.
 */
//reviewing
//ltt: least time to trigger
#if BMI160_CONFIG_FIFO_WML_CAL_ALGO_LTT
static void sns_dd_bmi160_fifo_calc_wml_ltt(sns_dd_bmi160_state_t   *state)
{
	bmi160_hw_mod_t         *hw_mod;
	bmi160_hw_mod_t         *hw_mod_fifo_master;

	uint32_t time_to_expire_acc = (uint32_t)-1;
	uint32_t time_to_expire_gyr = (uint32_t)-1;
	uint32_t time_to_expire_mag = (uint32_t)-1;

	uint32_t time_to_expire_min = (uint32_t)-1;

	uint16_t odr_acc_curr = 0;
	uint16_t odr_gyr_curr = 0;
	uint16_t odr_mag_curr = 0;
	sns_ddf_sensor_e ff_sync_master_sensor = SNS_DDF_SENSOR__NONE;

	uint32_t fc_when_time_expires_acc = 0;
	uint32_t fc_when_time_expires_gyr = 0;
	uint32_t fc_when_time_expires_mag = 0;

	uint32_t fc_when_time_expires_max = 0;

	uint32_t bytes_when_time_expires_max = 0;


	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_acc > 0)) {
		time_to_expire_acc = 1000000 / hw_mod->odr_curr * state->ff_wml_req_acc;
		odr_acc_curr = hw_mod->odr_curr;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_gyr > 0)) {
		time_to_expire_gyr = 1000000 / hw_mod->odr_curr * state->ff_wml_req_gyr;
		odr_gyr_curr = hw_mod->odr_curr;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_MAG);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_mag > 0)) {
		time_to_expire_mag = 1000000 / hw_mod->odr_curr * state->ff_wml_req_mag;
		odr_mag_curr = hw_mod->odr_curr;
	}


	BMI160_MSG_3(HIGH, "time_to_expire_min <%d %d %d> %d",
			time_to_expire_acc, time_to_expire_gyr, time_to_expire_mag);
	BMI160_MSG_3(HIGH, "odr_curr <%d %d %d>",
			odr_acc_curr, odr_gyr_curr, odr_mag_curr);

	time_to_expire_min = BST_MIN(time_to_expire_acc, time_to_expire_gyr);
	time_to_expire_min = BST_MIN(time_to_expire_min, time_to_expire_mag);

	if ((uint32_t)(-1) != time_to_expire_min) {
		if ((uint32_t)-1 != time_to_expire_acc) {
			fc_when_time_expires_acc = odr_acc_curr * (uint64_t)(time_to_expire_min / 1000) / 1000;
		}

		if ((uint32_t)-1 != time_to_expire_gyr) {
			fc_when_time_expires_gyr = odr_gyr_curr * (uint64_t)(time_to_expire_min / 1000) / 1000;
		}

		if ((uint32_t)-1 != time_to_expire_gyr) {
			fc_when_time_expires_mag = odr_mag_curr * (uint64_t)(time_to_expire_min / 1000) / 1000;
		}

		fc_when_time_expires_max = BST_MAX(fc_when_time_expires_acc, fc_when_time_expires_gyr);
		fc_when_time_expires_max = BST_MAX(fc_when_time_expires_max, fc_when_time_expires_mag);

		bytes_when_time_expires_max =
			BMI160_FF_DATA_LEN_ACC * fc_when_time_expires_acc +
			BMI160_FF_DATA_LEN_GYR * fc_when_time_expires_gyr +
			BMI160_FF_DATA_LEN_MAG * fc_when_time_expires_mag +
			+ fc_when_time_expires_max;

		BMI160_MSG_3(HIGH, "fc_when_time_expires_max <%d %d %d>",
				fc_when_time_expires_acc, fc_when_time_expires_gyr, fc_when_time_expires_mag);
	}

	//OUTPUT
	state->ff_wml = bytes_when_time_expires_max;
	state->ff_suggested_bytes2read = bytes_when_time_expires_max;
	BMI160_MSG_2(HIGH, "[calc_wml_ltt] ff_wml_bytes: %d ff_suggested_bytes2read: %d",
			state->ff_wml, state->ff_suggested_bytes2read);
}
#endif


//reviewing
//ndt: least delay triggering
//ASSUMPTION: the code can only support accel/gyr/mag in FIFO
#if BMI160_CONFIG_FIFO_WML_CAL_ALGO_LDT
static void sns_dd_bmi160_fifo_calc_wml_ldt(sns_dd_bmi160_state_t   *state)
{
	bmi160_hw_mod_t         *hw_mod;
	bmi160_hw_mod_t         *hw_mod_fifo_master;

	uint16_t odr_acc_curr = 0;
	uint16_t odr_gyr_curr = 0;
	uint16_t odr_mag_curr = 0;
	uint16_t odr_fifo_master  = 0;

	uint32_t fc_when_time_expires_acc = 0;
	uint32_t fc_when_time_expires_gyr = 0;
	uint32_t fc_when_time_expires_mag = 0;

	uint32_t fc_wml_master = 0;
	uint32_t fc_wml_acc_max = 0;
	uint32_t fc_wml_gyr_max = 0;
	uint32_t fc_wml_mag_max = 0;


	uint32_t bytes_when_time_expires_max = 0;
	uint32_t bytes_when_wml_fires = 0;

	hw_mod_fifo_master = sns_dd_bmi160_fifo_get_master(state);
	if (NULL == hw_mod_fifo_master) {
		state->ff_wml = 0;
		state->ff_suggested_bytes2read = 0;
		return;
	} else {
		odr_fifo_master = hw_mod_fifo_master->odr_curr;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_acc > 0)) {
		odr_acc_curr = hw_mod->odr_curr;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_gyr > 0)) {
		odr_gyr_curr = hw_mod->odr_curr;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_MAG);
	if ((NULL != hw_mod)
			&& (hw_mod->odr_curr > 0)
			&& (state->ff_wml_req_mag > 0)) {
		odr_mag_curr = hw_mod->odr_curr;
	}


	if (odr_fifo_master > 0) {
		if (odr_acc_curr > 0) {
			fc_when_time_expires_acc = odr_fifo_master / odr_acc_curr * state->ff_wml_req_acc;
		}

		if (odr_gyr_curr > 0) {
			fc_when_time_expires_gyr = odr_fifo_master / odr_gyr_curr * state->ff_wml_req_gyr;
		}

		if (odr_mag_curr > 0) {
			fc_when_time_expires_mag = odr_fifo_master / odr_mag_curr * state->ff_wml_req_mag;
		}

		fc_wml_master = bmi160_util_get_com_div(fc_when_time_expires_acc, fc_when_time_expires_gyr);
		fc_wml_master = bmi160_util_get_com_div(fc_wml_master, fc_when_time_expires_mag);

		if (odr_acc_curr > 0) {
			fc_wml_acc_max = odr_acc_curr / odr_fifo_master * fc_wml_master;
			fc_wml_acc_max = fc_wml_acc_max ? fc_wml_acc_max : 1;
		}

		if (odr_gyr_curr > 0) {
			fc_wml_gyr_max = odr_gyr_curr / odr_fifo_master * fc_wml_master;
			fc_wml_gyr_max = fc_wml_gyr_max ? fc_wml_gyr_max : 1;
		}

		if (odr_mag_curr > 0) {
			fc_wml_mag_max = odr_mag_curr / odr_fifo_master * fc_wml_master;
			fc_wml_mag_max = fc_wml_mag_max ? fc_wml_mag_max : 1;
		}

		bytes_when_time_expires_max =
			BMI160_FF_DATA_LEN_ACC * fc_wml_acc_max +
			BMI160_FF_DATA_LEN_GYR * fc_wml_gyr_max +
			BMI160_FF_DATA_LEN_MAG * fc_wml_mag_max +
			+ fc_wml_master;

		bytes_when_wml_fires =
			BMI160_FF_DATA_LEN_ACC * (odr_acc_curr * fc_wml_master / odr_fifo_master) +
			BMI160_FF_DATA_LEN_GYR * (odr_gyr_curr * fc_wml_master / odr_fifo_master) +
			BMI160_FF_DATA_LEN_MAG * (odr_mag_curr * fc_wml_master / odr_fifo_master) +
			+ fc_wml_master;
	} else {
		fc_wml_master = 0;
		bytes_when_time_expires_max = 0;
		bytes_when_wml_fires = 0;
	}

	//OUTPUT
	BMI160_MSG_3(HIGH, "odr_curr <%d %d %d>",
			odr_acc_curr, odr_gyr_curr, odr_mag_curr);

	BMI160_MSG_4(HIGH, "fc_when_time_expires<%d %d %d> fc_wml_master: %d",
			fc_when_time_expires_acc, fc_when_time_expires_gyr, fc_when_time_expires_mag, fc_wml_master);

	state->ff_wml = bytes_when_wml_fires;
	state->ff_suggested_bytes2read = bytes_when_time_expires_max;

	BMI160_MSG_2(HIGH, "[calc_wml_ldt] ff_wml_bytes: %d ff_suggested_bytes2read: %d",
			state->ff_wml, state->ff_suggested_bytes2read);
}
#endif


static sns_ddf_status_e sns_dd_bmi160_get_attr_odr(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_memhandler_s    *memhandler,
		void                    **value,
		uint32_t                *num_elems,
		int32_t                 caller)
{
	bmi160_hw_mod_t         *hw_mod;
	sns_ddf_odr_t           odr_req = 0;
	sns_ddf_odr_t           *odr;
	bmi160_sub_dev_t        *sub_dev;

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			odr_req = state->odr_acc_req;
			break;
		case SNS_DDF_SENSOR_TEMP:
			odr_req = state->odr_tem_req;
			break;
		case SNS_DDF_SENSOR_DOUBLETAP:
			odr_req = state->odr_dbt_req;
			break;
		case SNS_DDF_SENSOR_GYRO:
			odr_req = state->odr_gyr_req;
			break;
		case SNS_DDF_SENSOR_MAG:
			odr_req = state->odr_mag_req;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, sensor_type);
	if (NULL == hw_mod) {
		return SNS_DDF_EINVALID_PARAM;
	}

	sub_dev = sns_dd_bmi160_get_subdev_from_type(state, sensor_type);
        if (NULL == sub_dev) {
           return SNS_DDF_EINVALID_PARAM;
        }

	odr = sns_ddf_memhandler_malloc_ex(
			memhandler,
			sizeof(sns_ddf_odr_t),
			sub_dev->smgr_handle);

	if (!odr) {
		return SNS_DDF_ENOMEM;
	}

	if (SNS_DDF_SENSOR_TEMP != sensor_type) {
		if (odr_req) {
			*odr = hw_mod->odr_curr;
		} else {
			*odr = 0;
		}
	} else {
		//because SMGR will not set ODR for SNS_DDF_SENSOR_TEMP
		*odr = hw_mod->odr_curr;
	}

	*value = odr;
	*num_elems = 1;

	INSERT_TRACE_POINT(bmi160, *odr);

	BMI160_MSG_3(HIGH, "[get_attr_odr] sensor_type: %d odr_curr: %d odr: %d",
			sensor_type, hw_mod->odr_curr, *odr);

	return SNS_DDF_SUCCESS;
}

//reviewing
static sns_ddf_status_e sns_dd_bmi160_set_attr_range(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		void                    *value,
		int32_t                 caller)
{
	sns_ddf_status_e        status  = SNS_DDF_SUCCESS;
	uint8_t                 range_idx = *((uint8_t *)value);
	bmi160_hw_mod_t         *hw_mod;

	BMI160_MSG_4_F(HIGH,
			"55555523 [set_attr_range] state: %p sensor_type: %d range_idx: %d caller: %d",
			state, sensor_type, range_idx, caller);


	hw_mod = sns_dd_bmi160_get_hw_mod(state, sensor_type);
	if (NULL == hw_mod) {
		return SNS_DDF_EINVALID_PARAM;
	}

	/*! change the range for accel */
	if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
		if (range_idx >= BST_ARRAY_SIZE(BMI160_ACC_RANGE_REGV_LIST)) {
			return SNS_DDF_EINVALID_PARAM;
		} else {
			state->range_idx_acc = range_idx;
		}

		status = hw_mod->set_range(hw_mod, state->port_handle, range_idx);

		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
		if (range_idx >= BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST)) {
			return SNS_DDF_EINVALID_PARAM;
		} else {
			state->range_idx_gyr = range_idx;
		}

		status = hw_mod->set_range(hw_mod, state->port_handle, range_idx);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
#if BMI160_CONFIG_ENABLE_MAG_IF
	} else if (SNS_DDF_SENSOR_MAG == sensor_type) {
#endif
	} else {
		return SNS_DDF_EINVALID_PARAM;
	}

	return SNS_DDF_SUCCESS;
}

//reviewing

#if BMI160_CONFIG_ENABLE_MD
static sns_ddf_status_e sns_dd_bmi160_set_attr_motion_detect(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		void                    *value,
		int32_t                 caller)
{
	sns_ddf_status_e        status;
	bool                    enable = *(bool *)value;
	struct bmi160_hw_mod    *hw_mod;

	if (!sns_ddf_signal_irq_enabled()) {
		return SNS_DDF_EINVALID_PARAM;
	}

	hw_mod = sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);

	BST_IGNORE_WARNING_UNUSED_VAR(hw_mod);

	BMI160_MSG_4_F(HIGH,
			"55555521 [set_attr_md] sensor_type: %d enable: %d odr_acc_curr: %d caller: %d",
			sensor_type, enable, hw_mod ? hw_mod->odr_curr : 0, caller);

	if (enable) {
		status = sns_dd_bmi160_cfg_md_thresh(state);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		status = sns_dd_bmi160_cfg_md_dur(state);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		status = sns_dd_bmi160_cfg_int_md(state, true);

		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	} else {
		status = sns_dd_bmi160_cfg_int_md(state, false);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	}


	if (enable) {
		status = sns_dd_bmi160_signal_register(state);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		state->int_en_flags.bits.md = true;
	} else {
		state->int_en_flags.bits.md = false;
		status = sns_dd_bmi160_signal_deregister(state);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	}

	return SNS_DDF_SUCCESS;
}
#endif

//reviewed
static sns_ddf_status_e sns_dd_bmi160_set_attr_powerstate(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		void                    *value,
		int32_t                 caller)
{
	sns_ddf_status_e        status = SNS_DDF_SUCCESS;
	sns_ddf_powerstate_e    power_state = *(sns_ddf_powerstate_e *)value;

	bool                    hw_mode_change_needed = false;
	uint32_t                ref_cnt;
	bmi160_hw_mod_t         *hw_mod;

	INSERT_TRACE_POINT(bmi160, power_state);

	INSERT_TRACE_POINT4_T(bmi160, 0x20, 'p', sensor_type, power_state);

	hw_mod = sns_dd_bmi160_get_hw_mod(state, sensor_type);

	if (NULL == hw_mod) {
		return SNS_DDF_EINVALID_PARAM;
	}


	BMI160_MSG_4_F(HIGH,
			"55555521 [set_attr_ps] before sensor_type: %d power_state: %d hw_mod->ref_cnt: %d caller: %d",
			sensor_type, power_state, hw_mod->ref_cnt, caller);


	ref_cnt = hw_mod->ref_cnt;

	if (SNS_DDF_POWERSTATE_LOWPOWER == power_state) {
		if (ref_cnt > 0) {
			ref_cnt--;
			if (0 == ref_cnt) {
				hw_mode_change_needed = true;
			}
		}
	} else if (SNS_DDF_POWERSTATE_ACTIVE == power_state) {
		ref_cnt++;
		if (1 == ref_cnt) {
			hw_mode_change_needed = true;
		}
	}

	if (hw_mode_change_needed) {
		status = hw_mod->set_power_state(
				hw_mod,
				state->port_handle,
				power_state);

		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		if (SNS_DDF_POWERSTATE_LOWPOWER != power_state) {
			if (hw_mod->odr_map_idx >= 0) {
				hw_mod->odr_curr = BMI160_REGV_ODR_MAP[hw_mod->odr_map_idx].l;
			}
		}

		sns_dd_bmi160_update_hw_mod_odr_max(state);
	}

	hw_mod->ref_cnt = ref_cnt;

	BMI160_MSG_3_F(HIGH, "55555521 [set_attr_ps] after sensor_type: %d power_state: %d hw_mod->ref_cnt: %d",
			sensor_type, power_state, hw_mod->ref_cnt);

	return SNS_DDF_SUCCESS;
}

//reviewed
static sns_ddf_status_e sns_dd_bmi160_set_attr_odr(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		void                    *value,
		int32_t                 caller)
{
	sns_ddf_status_e        status;

	bmi160_sub_dev_t        *sub_dev;
	bmi160_hw_mod_t         *hw_mod;

	sns_ddf_odr_t           odr_curr;
	sns_ddf_odr_t           odr_matched;

	sns_ddf_odr_t           odr_req = *((sns_ddf_odr_t *)value);

	int32_t                 odr_map_idx;

	uint8_t                 regv_fifo_config_1;
	uint8_t                 si_buf_wr;

	INSERT_TRACE_POINT(bmi160, odr_req);
	INSERT_TRACE_POINT4_T(bmi160, 0x20, 'o', sensor_type, odr_req);

	hw_mod  = sns_dd_bmi160_get_hw_mod(state, sensor_type);

	if (NULL == hw_mod) {
		return SNS_DDF_EINVALID_PARAM;
	}

	odr_curr = hw_mod->odr_curr;

	BMI160_MSG_4_F(ERROR,
			"5555552d [set_attr_odr] enter sensor_type: %d odr_curr: %d odr_req: %d caller: %d",
			sensor_type, odr_curr, odr_req, caller);


	status = hw_mod->get_best_match_odr(hw_mod, sensor_type, odr_req, &odr_matched);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (odr_matched > 0) {
		odr_map_idx = bmi160_get_matching_odr_map_idx(odr_matched);
		if (odr_map_idx < 0) {
			return SNS_DDF_EINVALID_PARAM;
		}

		//<fifo_handling>
		if (state->ff_wml > 0) {
			status = sns_dd_bmi160_fifo_flush(state, 0, 1);

			regv_fifo_config_1 = 0x00;
			status = bmi160_sbus_read_wrapper(
					state->port_handle,
					BMI160_REGA_USR_FIFO_CONFIG_1,
					&regv_fifo_config_1,
					1);

			si_buf_wr = 0x00;
			status = bmi160_sbus_write_wrapper(
					state->port_handle,
					BMI160_REGA_USR_FIFO_CONFIG_1,
					&si_buf_wr,
					1);
		}
		//</fifo_handling>

		status = hw_mod->set_odr(hw_mod, state->port_handle,
				BMI160_REGV_ODR_MAP[odr_map_idx].r);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		hw_mod->odr_curr = BMI160_REGV_ODR_MAP[odr_map_idx].l;
		hw_mod->odr_map_idx = odr_map_idx;

		//<fifo_handling>
		state->ff_sample_sync_info.avail_last_ts = 0;
		if (state->ff_wml > 0) {
			//mark this as 0 so sns_dd_bmi160_fifo_populate_sample_ts() can take right decisions
			sns_dd_bmi160_fifo_reset_state(state);
			sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_FIFO_FLUSH);

			status = bmi160_sbus_write_wrapper(
					state->port_handle,
					BMI160_REGA_USR_FIFO_CONFIG_1,
					&regv_fifo_config_1,
					1);
		}
		//</fifo_handling>

		status = bmi160_get_reg_hw_err_stat(state->port_handle, &state->hw_err_st);
		if (state->hw_err_st.regv) {
			sns_dd_bmi160_handle_device_err(state, &state->hw_err_st);
			//return SNS_DDF_EDEVICE;
		}

		sns_dd_bmi160_update_hw_mod_odr_max(state);

	} else {
		sns_ddf_powerstate_e power_state = SNS_DDF_POWERSTATE_LOWPOWER;
		status = sns_dd_bmi160_set_attr_powerstate(state,
				sensor_type, &power_state, 2);

		hw_mod->odr_curr = 0;
	}


	if (SNS_DDF_SENSOR_DOUBLETAP == sensor_type) {
		if (odr_req > 0) {
			status = sns_dd_bmi160_cfg_int_doubletap(state, true);
		} else {
			status = sns_dd_bmi160_cfg_int_doubletap(state, false);
		}
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		sub_dev = sns_dd_bmi160_get_subdev_from_type(state,
				SNS_DDF_SENSOR_ACCEL);

		BMI160_MSG_1(ERROR, "sub_dev: %p", sub_dev);
		if ((sub_dev != NULL)
				&& (state->odr_acc_req > 0)
				&& (odr_curr != hw_mod->odr_curr)) {
			sns_ddf_smgr_notify_event(sub_dev->smgr_handle,
					SNS_DDF_SENSOR_ACCEL,
					SNS_DDF_EVENT_ODR_CHANGED);
#if BMI160_CONFIG_ENABLE_LOG_DATA_L1
			BMI160_MSG_0(ERROR, "event: SNS_DDF_EVENT_ODR_CHANGED");
#endif
		}
	}

	BMI160_MSG_3_F(ERROR, "5555552d [set_attr_odr] exit  sensor_type: %d odr_curr: %d odr_req: %d",
			sensor_type, hw_mod->odr_curr, odr_req);

	return SNS_DDF_SUCCESS;
}

//reviewing
static sns_ddf_status_e sns_dd_bmi160_set_attr_fifo(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		void                    *value,
		int32_t                 caller)
{
	sns_ddf_status_e        status;
	uint16_t                desired_wml = *(uint16_t *)value;
	uint8_t                 arbitrated_wml_reg;

	BMI160_MSG_3_F(HIGH, "[set_attr_fifo] sensor_type: %d wml_frames: %d caller: %d",
			sensor_type, desired_wml, caller);

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			state->ff_wml_req_acc = desired_wml;
			break;
		case SNS_DDF_SENSOR_GYRO:
			state->ff_wml_req_gyr = desired_wml;
			break;
		case SNS_DDF_SENSOR_MAG:
			state->ff_wml_req_mag = desired_wml;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	sns_dd_bmi160_fifo_reset_state(state);
#if BMI160_CONFIG_FIFO_WML_CAL_ALGO_LTT
	sns_dd_bmi160_fifo_calc_wml_ltt(state);
#endif

#if BMI160_CONFIG_FIFO_WML_CAL_ALGO_LDT
	sns_dd_bmi160_fifo_calc_wml_ldt(state);
#endif

	if (state->ff_wml > BMI160_FF_WML_MAX) {
		state->ff_wml = BMI160_FF_WML_MAX;
		state->ff_suggested_bytes2read = BMI160_FF_WML_MAX;
	}

	arbitrated_wml_reg = state->ff_wml >> 2;

	status = bmi160_set_reg_fifo_wml(state->port_handle, arbitrated_wml_reg);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	//set fifo_config_1
	union bmi160_fifo_config_1      fifo_config_1;
	//fifo_config_1
	fifo_config_1.reg = 0;
	fifo_config_1.bits.fifo_stop_on_full      = 0;
	fifo_config_1.bits.fifo_time_en           = 1;
	fifo_config_1.bits.fifo_header_en         = 1;
	fifo_config_1.bits.fifo_tag_int1_en       = 0;
	fifo_config_1.bits.fifo_tag_int2_en       = 0;

	if (state->ff_wml_req_acc > 0) {
		fifo_config_1.bits.fifo_acc_en = 1;
	}

	if (state->ff_wml_req_gyr > 0) {
		fifo_config_1.bits.fifo_gyr_en = 1;
	}

	if (state->ff_wml_req_mag > 0) {
		fifo_config_1.bits.fifo_mag_en = 1;
	}

	status = bmi160_set_reg_fifo_config_1(
			state->port_handle,
			&fifo_config_1);

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);


	return status;
}

static sns_ddf_status_e sns_dd_bmi160_enable_sched_data_agm(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		bool                    enable)
{
	sns_ddf_status_e status;

	bool            int_drdy_needed;
	bool            int_fifo_needed;

	uint16_t        int_fifo_en;
	uint16_t        int_drdy_en;

	int_drdy_en = state->int_en_flags.bits.drdy.flag;
	int_fifo_en = state->int_en_flags.bits.fifo.flag;

	if (enable) {
		if (state->ff_wml > 0) {
			if (!state->int_en_flags.bits.fifo.flag) {
				status = sns_dd_bmi160_cfg_int_fifo_wml(state, true);
				BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

			}
			status = sns_dd_bmi160_set_int_fifo_flag(state, sensor_type, true);
			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		} else {
			if (!state->int_en_flags.bits.drdy.flag) {
				status = sns_dd_bmi160_cfg_int_drdy(state, true);
				BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
			}
			status = sns_dd_bmi160_set_int_drdy_flag(state, sensor_type, true);
			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		}
	} else {
		//ASSUMPTION: for one sensor, DRDY or FIFO INT is exclusive
		status = sns_dd_bmi160_set_int_drdy_flag(state, sensor_type, false);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		status = sns_dd_bmi160_set_int_fifo_flag(state, sensor_type, false);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		int_drdy_needed = state->int_en_flags.bits.drdy.flag;

		int_fifo_needed = state->int_en_flags.bits.fifo.flag;

		if (!int_drdy_needed && int_drdy_en) {
			status = sns_dd_bmi160_cfg_int_drdy(state, false);
			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		}
		status = sns_dd_bmi160_set_int_drdy_flag(state, sensor_type, false);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		if (!int_fifo_needed && int_fifo_en) {
			status = sns_dd_bmi160_cfg_int_fifo_wml(state, false);
			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		}
		status = sns_dd_bmi160_set_int_fifo_flag(state, sensor_type, false);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		//mark this as 0 so sns_dd_bmi160_fifo_populate_sample_ts() can take right decisions
	}

	return SNS_DDF_SUCCESS;
}

//reviewed
/**
 * @brief Validate and initialize the tap settings
 */
void sns_dd_bmi160_tap_settings_init(
		bmi160_tap_settings_s           *tap_settings,
		const sns_dd_bmi160_nv_params_s *nv_params)
{
	if (tap_settings == NULL)
		return;

	tap_settings->th        = BMI160_CONFIG_ACC_TAP_TH_2G;
	tap_settings->shock     = BMI160_CONFIG_ACC_TAP_SHOCK;
	tap_settings->quiet     = BMI160_CONFIG_ACC_TAP_QUIET;
	tap_settings->dur       = BMI160_CONFIG_ACC_TAP_DUR;
	BMI160_MSG_3_F(ERROR, "%d %p %p",
			55555702, tap_settings, nv_params);

	// If no nv_params are specified, then keep the default
	if (nv_params == NULL) {
		BMI160_MSG_3_F(ERROR, "%d %d %d",
				55555703, 55555703, 55555703);
		return;
	}

	// Check to see if the nv_params contains tap-settings by validating the magic number
	//if (BST_NVM_MAGIC == nv_params->magic_num)
	//TODO:
	if (0) {
		/*!The registry magic number is correct. Loading NV params...*/
		BMI160_MSG_3_F(ERROR, "%d %d %d",
				55555704, nv_params->th, nv_params->shock);
		BMI160_MSG_3_F(ERROR, "%d %d %d",
				55555705, nv_params->quiet, nv_params->dur);

		tap_settings->th = nv_params->th;
		tap_settings->shock = nv_params->shock;
		tap_settings->quiet = nv_params->quiet;
		tap_settings->dur = nv_params->dur;

	} else {
		/*!Incorrect registry magic number specified, using defaults...*/
		BMI160_MSG_0(ERROR, "incorrect nv_params passed for tap settings");
		return;
	}
}

void sns_dd_bmi160_prepare_caches(sns_dd_bmi160_state_t *state)
{
	state->sensor_data_cache.samples = state->sensor_data_cache_samples;

	state->sensor_data_cache_a.samples = state->sensor_data_cache_samples_a;
	state->sensor_data_cache_a.num_samples = 3;
	state->sensor_data_cache_a.status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_a.sensor = SNS_DDF_SENSOR_ACCEL;
	state->sensor_data_cache_a.samples[0].status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_a.samples[1].status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_a.samples[2].status = SNS_DDF_SUCCESS;


	state->sensor_data_cache_g.samples = state->sensor_data_cache_samples_g;
	state->sensor_data_cache_g.num_samples = 3;
	state->sensor_data_cache_g.status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_g.sensor = SNS_DDF_SENSOR_GYRO;
	state->sensor_data_cache_g.samples[0].status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_g.samples[1].status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_g.samples[2].status = SNS_DDF_SUCCESS;


	state->sensor_data_cache_t.samples = state->sensor_data_cache_samples_t;
	state->sensor_data_cache_t.num_samples = 1;
	state->sensor_data_cache_t.sensor = SNS_DDF_SENSOR_TEMP;
	state->sensor_data_cache_t.status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_t.samples[0].status = SNS_DDF_SUCCESS;

#if BMI160_CONFIG_ENABLE_INT_DOUBLE_TAP
	state->sensor_data_cache_dt.samples = state->sensor_data_cache_samples_dt;
	state->sensor_data_cache_dt.num_samples = 1;
	state->sensor_data_cache_dt.sensor = SNS_DDF_SENSOR_DOUBLETAP;
	state->sensor_data_cache_dt.status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_dt.samples[0].status = SNS_DDF_SUCCESS;
#endif

	state->ff_cache_a.samples = state->ff_cache_samples_a.samples;
	state->ff_cache_a.status = SNS_DDF_SUCCESS;
	state->ff_cache_a.sensor = SNS_DDF_SENSOR_ACCEL;


	state->ff_cache_g.samples = state->ff_cache_samples_g.samples;

	state->ff_cache_g.status = SNS_DDF_SUCCESS;
	state->ff_cache_g.sensor = SNS_DDF_SENSOR_GYRO;
#if BMI160_CONFIG_ENABLE_MAG_IF
	state->sensor_data_cache_m.samples = state->sensor_data_cache_samples_m;
	state->sensor_data_cache_m.num_samples = 3;
	state->sensor_data_cache_m.status = SNS_DDF_SUCCESS;
	state->sensor_data_cache_m.sensor = SNS_DDF_SENSOR_MAG;

	state->ff_cache_m.samples = state->ff_cache_samples_m.samples;
	state->ff_cache_m.status = SNS_DDF_SUCCESS;
	state->ff_cache_m.sensor = SNS_DDF_SENSOR_MAG;
#endif

}

//reviewing
//TODO: parse for gyro/mag etc as well
/**
 * @brief Parses the nv_params and fills in appropriate values for the axes_map
 *        and the tap_settings (if applicable)
 */
sns_ddf_status_e sns_dd_bmi160_parse_nv_params(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_nv_params_s     *entire_nv_params,
		sns_ddf_sensor_e        sensors[])
{
	sns_ddf_axes_map_s              *axes_map = NULL;
	uint8_t                         *registry_data = NULL;;
	bmi160_tap_settings_s           *tap_settings = NULL;

	BMI160_MSG_1(ERROR, "[parse_nv_params] sensor_type: %d", sensors[0]);
	// If there are no nv_params handed in, then set all to default values
	if (SNS_DDF_SENSOR_ACCEL == sensors[0]) {
		axes_map = &state->axes_map_acc;
	} else if (SNS_DDF_SENSOR_GYRO == sensors[0]) {
		axes_map = &state->axes_map_gyr;
	} else if (SNS_DDF_SENSOR_MAG == sensors[0]) {
		axes_map = &state->axes_map_mag;
	} else if (SNS_DDF_SENSOR_DOUBLETAP == sensors[0]) {
		tap_settings = &state->tap_settings;
	}

	if (NULL == entire_nv_params) {
		registry_data = NULL;
	} else {
		if (NULL == entire_nv_params->data) {
			BMI160_MSG_0(ERROR, "[parse_nv_params] no nv ram data");
		}
		registry_data = entire_nv_params->data;
	}

	if (axes_map) {
		sns_ddf_axes_map_init(axes_map, registry_data);
		if (registry_data) {
			BMI160_MSG_3_F(ERROR, "[parse_nv_params] %d %d %d",
					axes_map->indx_x, axes_map->indx_y, axes_map->indx_z);
			BMI160_MSG_3_F(ERROR, "[parse_nv_params] %d %d %d",
					axes_map->sign_x, axes_map->sign_y, axes_map->sign_z);
		}
	}

	if (tap_settings) {
		sns_dd_bmi160_tap_settings_init(tap_settings, (sns_dd_bmi160_nv_params_s*)registry_data);
	}

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_bmi160_run_test_self(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                *err)
{
	sns_ddf_status_e        status = SNS_DDF_SUCCESS;
	uint8_t                 si_buf = 0;

	status = bmi160_sbus_read_wrapper(state->port_handle,
			BMI160_REGA_USR_CHIP_ID,
			&si_buf,
			1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (BMI160_REGV_CHIP_ID_MAJOR != (si_buf & BMI160_REGV_CHIP_ID_MAJOR)) {
		*err = si_buf;
		return SNS_DDF_EDEVICE;
	}

	*err = 0;
	return SNS_DDF_SUCCESS;
}

//reviewing
#if BMI160_CONFIG_ENABLE_SELFTEST
static void sns_dd_bmi160_test_notify(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_status_e        status,
		uint32_t                err,
		q16_t                   *biases)
{
	bmi160_sub_dev_t        *sub_dev;
	q16_t                   *biases_ptr;
	uint8_t                 i;
	sns_dd_bmi160_state_t   *state;
	uint32_t                caller = ('t' << 8) | 'o';


	state = sns_dd_bmi160_get_dev(dd_handle);

	if (!state) {
		return;
	}

	state->test_inertial_in_progress = 0;

	sub_dev = sns_dd_bmi160_get_subdev_from_type(
			state,
			sensor_type);

	if (!sub_dev) {
		return;
	}

	if (SNS_DD_ITEST_ZERO_VARIANCE == err) {
		/* Overwrite err with SNS_DD_ITEST_SUCCESS and
		 * status with SNS_DDF_SUCCESS in case of zero variance */
		sns_ddf_smgr_notify_test_complete(sub_dev->smgr_handle,
				sensor_type,
				SNS_DDF_SUCCESS, SNS_DD_ITEST_SUCCESS);
	} else {
		sns_ddf_smgr_notify_test_complete(sub_dev->smgr_handle,
				sensor_type,
				status, err);
	}

	if ((SNS_DDF_SUCCESS == status) || (SNS_DD_ITEST_ZERO_VARIANCE == err)) {
		if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
			biases_ptr = state->bias_acc;
		} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
			biases_ptr = state->bias_gyr;
		} else {
			biases_ptr = NULL;
			return;
		}

		for (i = 0; i < SDD_ACC_NUM_AXIS; i++) {
			biases_ptr[i] = biases[i];
		}

		sns_ddf_smgr_notify_event(sub_dev->smgr_handle,
				sensor_type,
				SNS_DDF_EVENT_BIAS_READY);
#if BMI160_CONFIG_ENABLE_LOG_DATA_L0
			BMI160_MSG_0(ERROR, "event: SNS_DDF_EVENT_BIAS_READY");
#endif
	}

	sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_SOFT_RESET);
	sns_ddf_delay(100000);
	sns_dd_bmi160_reset_state(state, sensor_type, caller);
}

static sns_ddf_status_e sns_dd_bmi160_run_test_oem(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                *err)
{
	sns_ddf_status_e                status;
	sns_dd_inertial_test_config_s   test_config;
	uint8_t                         range_idx;
	sns_ddf_powerstate_e            power_state;
	sns_ddf_odr_t                   odr_req;
	sns_dd_bmi160_state_t           *state;
	uint32_t                        caller = ('t' << 8) | 'o';

	state = sns_dd_bmi160_get_dev(dd_handle);

	if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
		test_config.sample_rate =  20;
		test_config.num_samples =  64;
		test_config.max_variance = (int64_t)(FX_CONV((FX_FLTTOFIX_Q16(0.3)), 16, 32));
		test_config.bias_thresholds[0] = FX_FLTTOFIX_Q16(0.2 * G);
		test_config.bias_thresholds[1] = FX_FLTTOFIX_Q16(0.2 * G);
		test_config.bias_thresholds[2] = FX_FLTTOFIX_Q16(0.26 * G);

		odr_req = 200;
		range_idx = 1;  //+/-4G
	} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
		test_config.sample_rate =  20;
		test_config.num_samples =  64;
		test_config.max_variance = (int64_t)(FX_CONV((FX_FLTTOFIX_Q16(0.1)), 16, 32));
		test_config.bias_thresholds[0] = FX_FLTTOFIX_Q16(0.087);
		test_config.bias_thresholds[1] = FX_FLTTOFIX_Q16(0.087);
		test_config.bias_thresholds[2] = FX_FLTTOFIX_Q16(0.087);

		odr_req = 200;
		range_idx = BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST) - 1;
	} else {
		status = SNS_DDF_EINVALID_TEST;
		*err = (sensor_type << 8) | 0;
		goto exit_err_test_oem;
	}

	/*! soft reset */
	status = sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_SOFT_RESET);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 1;
		goto exit_err_test_oem;
	}

	sns_ddf_delay(100000);

	//prepare the settings before the testing

	status = sns_dd_bmi160_set_attr_range(state, sensor_type, &range_idx, caller);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 2;
		goto exit_err_test_oem;
	}

	power_state = SNS_DDF_POWERSTATE_ACTIVE;
	status = sns_dd_bmi160_set_attr_powerstate(state, sensor_type,
			&power_state, caller);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 3;
		goto exit_err_test_oem;
	}

	status = sns_dd_bmi160_set_attr_odr(state, sensor_type, &odr_req, caller);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 4;
		goto exit_err_test_oem;
	}

	status = sns_dd_inertial_test_run(
			sensor_type,
			dd_handle,
			&SNS_DD_IF_BMI160,
			&test_config,
			&sns_dd_bmi160_test_notify);

	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 5;
		goto exit_err_test_oem;
	}

exit_err_test_oem:
	BMI160_MSG_3(HIGH,
			"[run_test_sw_oem] sensor_type: %d status: %d err: 0x%x",
			sensor_type, status, *err);

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (*err || (SNS_DDF_SUCCESS != status)) {
		return status;
	}

	*err = 0;
	state->test_inertial_in_progress = 1;
	return SNS_DDF_PENDING;
}

static sns_ddf_status_e sns_dd_bmi160_run_test_sw_hw(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                *err)
{
	sns_ddf_status_e        status;
	uint8_t                 regv;
	uint32_t                caller = ('t' << 8) | 'w';

	/*! soft reset */
	status = sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_SOFT_RESET);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 1;
		goto exit_err_test_sw_hw;
	}

	sns_ddf_delay(100000);
	sns_ddf_powerstate_e    power_state;

	power_state = SNS_DDF_POWERSTATE_ACTIVE;
	sns_dd_bmi160_set_attr_powerstate(state, sensor_type, &power_state, caller);

	if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
		/*! set to +/-8G range */
		uint8_t                 range_idx = 2; /* +/- 8G */
		sns_ddf_odr_t           odr_req = 1600;

		struct bmi160_val_acc   val1_acc_static = {0};
		struct bmi160_val_acc   val2_acc_static = {0};
		uint8_t                 si_buf_rd[7] = "";
		int32_t                 diff_val_acc_static = 0;

		//prepare for the self test
		status = sns_dd_bmi160_set_attr_range(state, sensor_type, &range_idx, caller);

		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 2;
			goto exit_err_test_sw_hw;
		}

		status = sns_dd_bmi160_set_attr_odr(state, sensor_type, &odr_req, caller);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 3;
			goto exit_err_test_sw_hw;
		}
		sns_ddf_delay(10000);   //10ms

		//start the self test process
		//<test_acc>

		//<test_acc_x>
		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 3);                //high-amp
		regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, 1);     //axis-x
		regv = BST_SET_VAL_BIT(regv, 2);                //positive
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);

		sns_ddf_delay(BMI160_SPEC_ACC_SELF_TEST_WAIT_TIME_MS * 1000);

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_DATA_14, si_buf_rd, 6);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 4;
			goto exit_err_test_sw_hw;
		}

		bmi160_parse_data_acc(si_buf_rd, 6, &val1_acc_static);

		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 3);                //high-amp
		regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, 1);     //axis-x
		regv = BST_CLR_VAL_BIT(regv, 2);                //negative
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);

		sns_ddf_delay(BMI160_SPEC_ACC_SELF_TEST_WAIT_TIME_MS * 1000);

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_DATA_14, si_buf_rd, 6);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 5;
			goto exit_err_test_sw_hw;
		}

		bmi160_parse_data_acc(si_buf_rd, 6, &val2_acc_static);

		diff_val_acc_static = (int32_t)val1_acc_static.x - (int32_t)val2_acc_static.x;
		BMI160_MSG_3(HIGH, "diff_val_acc_static_x: <%d %d %d>",
				val1_acc_static.x,
				val2_acc_static.x,
				diff_val_acc_static);

		/* 800mg for x axis */
		if (BST_ABS(diff_val_acc_static) < 3277) {
			*err = (sensor_type << 8) | 6;
			status = SNS_DDF_EFAIL;
			goto exit_err_test_sw_hw;
		}
		//</test_acc_x>

		//<test_acc_y>
		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 3);                //high-amp
		regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, 2);     //axis-y
		regv = BST_SET_VAL_BIT(regv, 2);                //positive
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);

		sns_ddf_delay(BMI160_SPEC_ACC_SELF_TEST_WAIT_TIME_MS * 1000);

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_DATA_14, si_buf_rd, 6);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 7;
			goto exit_err_test_sw_hw;
		}

		bmi160_parse_data_acc(si_buf_rd, 6, &val1_acc_static);

		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 3);                //high-amp
		regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, 2);     //axis-y
		regv = BST_CLR_VAL_BIT(regv, 2);                //negative
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);

		sns_ddf_delay(BMI160_SPEC_ACC_SELF_TEST_WAIT_TIME_MS * 1000);

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_DATA_14, si_buf_rd, 6);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 8;
			goto exit_err_test_sw_hw;
		}

		bmi160_parse_data_acc(si_buf_rd, 6, &val2_acc_static);

		diff_val_acc_static = (int32_t)val1_acc_static.y - (int32_t)val2_acc_static.y;
		BMI160_MSG_3(HIGH, "diff_val_acc_static_y: <%d %d %d>",
				val1_acc_static.y,
				val2_acc_static.y,
				diff_val_acc_static);

		/* 800mg for y axis */
		if (BST_ABS(diff_val_acc_static) < 3277) {
			*err = (sensor_type << 8) | 9;
			status = SNS_DDF_EFAIL;
			goto exit_err_test_sw_hw;
		}
		//</test_acc_y>

		//<test_acc_z>
		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 3);                //high-amp
		regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, 3);     //axis-z
		regv = BST_SET_VAL_BIT(regv, 2);                //positive
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);

		sns_ddf_delay(BMI160_SPEC_ACC_SELF_TEST_WAIT_TIME_MS * 1000);

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_DATA_14, si_buf_rd, 6);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 10;
			goto exit_err_test_sw_hw;
		}

		bmi160_parse_data_acc(si_buf_rd, 6, &val1_acc_static);

		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 3);                //high-amp
		regv = BST_SET_VAL_BITBLOCK(regv, 0, 1, 3);     //axis-z
		regv = BST_CLR_VAL_BIT(regv, 2);                //negative
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);

		sns_ddf_delay(BMI160_SPEC_ACC_SELF_TEST_WAIT_TIME_MS * 1000);

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_DATA_14, si_buf_rd, 6);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 11;
			goto exit_err_test_sw_hw;
		}

		bmi160_parse_data_acc(si_buf_rd, 6, &val2_acc_static);

		diff_val_acc_static = (int32_t)val1_acc_static.z - (int32_t)val2_acc_static.z;

		BMI160_MSG_3(HIGH, "diff_val_acc_static_z: <%d %d %d>",
				val1_acc_static.z,
				val2_acc_static.z,
				diff_val_acc_static);
		/* 400mg for z axis */
		if (BST_ABS(diff_val_acc_static) < 1639) {
			*err = (sensor_type << 8) | 12;
			status = SNS_DDF_EFAIL;
			goto exit_err_test_sw_hw;
		}
		//</test_acc_z>
		//</test_acc>

		status = SNS_DDF_SUCCESS;
	} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
		regv = 0;
		regv = BST_SET_VAL_BIT(regv, 4);

		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_SELF_TEST, &regv, 1);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 2;
			goto exit_err_test_sw_hw;
		}

		sns_ddf_delay(BMI160_SPEC_GYR_SELF_TEST_WAIT_TIME_MS * 1000);

		regv = 0;
		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_STATUS, &regv, 1);
		if (SNS_DDF_SUCCESS != status) {
			*err = (sensor_type << 8) | 3;
			goto exit_err_test_sw_hw;
		}

		if (!(B1_SET & regv)) {
			*err = (sensor_type << 8) | 4;
			status = SNS_DDF_EFAIL;
			goto exit_err_test_sw_hw;
		}

	} else if (SNS_DDF_SENSOR_MAG == sensor_type) {
#if BMI160_CONFIG_ENABLE_MAG_IF
		//TODO: MAG
#endif
	}

exit_err_test_sw_hw:
	BMI160_MSG_3(HIGH, "[run_test_sw_hw] sensor_type: %d status: %d err: 0x%x",
			sensor_type, status, *err);

	/*! soft reset */
	status = sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_SOFT_RESET);
	sns_ddf_delay(100000);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_bmi160_run_test_irq(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		uint32_t                *err)
{
	sns_ddf_status_e        status;
	bool                    enable = true;
	int32_t                 caller = ('t' << 8) | 'i';
	uint8_t                 range_idx;
	sns_ddf_odr_t           odr_req;
	sns_ddf_powerstate_e    power_state;

	status = sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_SOFT_RESET);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 1;
		goto exit_err_test_irq;
	}

	sns_ddf_delay(100000);

	//prepare for the test
	range_idx = 1;  //+/-4G
	status = sns_dd_bmi160_set_attr_range(state, sensor_type, &range_idx, caller);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 2;
		goto exit_err_test_irq;
	}

	power_state = SNS_DDF_POWERSTATE_ACTIVE;
	status = sns_dd_bmi160_set_attr_powerstate(state, sensor_type,
			&power_state, caller);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 3;
		goto exit_err_test_irq;
	}

	odr_req = 200;
	status = sns_dd_bmi160_set_attr_odr(state, sensor_type, &odr_req, caller);
	if (SNS_DDF_SUCCESS != status) {
		*err = (sensor_type << 8) | 4;
		goto exit_err_test_irq;
	}

	status = sns_dd_bmi160_set_attr_motion_detect(
			state, sensor_type, &enable, caller);

	BMI160_MSG_0(HIGH,
			"[run_test_sw_irq] MOTION DETECT enabled, you have 3 seconds to move the device");
	sns_ddf_delay(3000000);
exit_err_test_irq:
	BMI160_MSG_3(HIGH,
			"[run_test_sw_irq] sensor_type: %d status: %d err: 0x%x",
			sensor_type, status, *err);

	/*! soft reset */
	status = sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_SOFT_RESET);
	sns_ddf_delay(100000);

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}
#endif


#if DEBUG
static void cd2__________________________________________________dummy()
{
}
#endif

/*!
 *  @brief Initializes the 3 axis Bosch accelerometer BMI160
 *              determines the device to use
 *
 *  @detail
 *
 * @param[out] dd_handle_ptr  Pointer that this function must malloc and
 *                             populate. This is a handle to the driver
 *                             instance that will be passed in to all
 *                             other functions.
 *  @param[in]  smgr_handle    Handle used to identify this driver when it
 *                             calls into Sensors Manager functions.
 *  @param[in]  nv_params      NV parameters retrieved for the driver.
 *  @param[in]  device_info    Information describing each of the physical
 *                             devices controlled by this driver. This is
 *                             used to configure the bus and talk to the
 *                             device.
 *  @param[in]  memhandler     Memory handler used to dynamically allocate
 *                             output parameters, if applicable. NB: Do
 *                             not use memhandler to allocate memory for
 *                             @a dd_handle_ptr.
 * @param[in]  num_devices    Length of @a device_info.
 * @param[out] sensors        List of supported sensors, populated and
 returned by this function.
 *  @param[out] num_sensors    Length of @a sensors.
 *
 *
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
sns_ddf_status_e sns_dd_bmi160_init(
		sns_ddf_handle_t        *dd_handle_ptr,
		sns_ddf_handle_t        smgr_handle,
		sns_ddf_nv_params_s     *nv_params,
		sns_ddf_device_access_s device_info[],
		uint32_t                num_devices,
		sns_ddf_memhandler_s    *memhandler,
		sns_ddf_sensor_e        *sensors[],
		uint32_t                *num_sensors)
{
	sns_ddf_status_e        status;
	sns_dd_bmi160_state_t   *state;
	sns_ddf_sensor_e        *sensors_init;
	sns_ddf_handle_t        port_handle;
	int32_t                 i;

#if BMI160_CONFIG_ENABLE_UIMAGE
	sns_ddf_smgr_set_uimg_refac(smgr_handle);
#endif

#if BMI160_CONFIG_RUN_ON_OSSC_V1
	*sensors = &bmi160_sensor_list_sub_devs[bmi160_sensor_list_sub_dev_idx];
	bmi160_sensor_list_sub_dev_idx++;

	*num_sensors = BMI160_MAX_SENSORS_NUM;
#endif

#if BMI160_CONFIG_RUN_ON_OSSC
	if (NULL == bmi160_sns_port_handle_singleton) {
		status = sns_ddf_open_port(&port_handle,
				&device_info->port_config);
		bmi160_sns_port_handle_singleton = port_handle;
	}
#endif

	INSERT_TRACE_POINT(bmi160, 0x00);

	BMI160_MSG_3_F(ERROR, "%d %p %d",
			55555500, smgr_handle, device_info->first_gpio);
	BMI160_MSG_3_F(ERROR, "%d %d %d",
			55555500, nv_params->nvitem_grp, nv_params->nvitem_id);


	INSERT_TRACE_POINT(bmi160, 0x01);

	if (dd_handle_ptr == NULL || num_sensors == NULL
			|| sensors == NULL || memhandler == NULL) {
		BMI160_MSG_0(ERROR, "BMI160_init: Null Pointer argument found.");
		return SNS_DDF_EINVALID_PARAM;
	}
	INSERT_TRACE_POINT(bmi160, 0x02);


	BMI160_MSG_3_F(ERROR, "55555501 bmi160_init: number of sensors: %u first sensor: %u gpio1: %d",
			*num_sensors, (*sensors)[0], device_info->first_gpio);
	BMI160_MSG_3_F(ERROR, "55555501 %d %d %d",
			(*sensors)[0], (*sensors)[1], (*sensors)[2]);

	INSERT_TRACE_POINT(bmi160, 0x03);
	INSERT_TRACE_POINT3(bmi160, (*sensors)[0], (*sensors)[1], (*sensors)[2]);


	state = sns_dd_bmi160_find_same_dev(&device_info->port_config, *sensors, *num_sensors);
	BMI160_MSG_3_F(ERROR, "%d %p %d",
			55555501, state, *num_sensors);

	if (NULL == state) {
		for (i = 0; i < *num_sensors; i++) {
			if (SNS_DDF_SENSOR_MAG == (*sensors)[i]) {
				//the master (BMI160) is not initialized yet, so we are not able to
				//initialize the slave
				return SNS_DDF_EINVALID_PARAM;
			}
		}
	}

	INSERT_TRACE_POINT(bmi160, 0x04);
	if (NULL == state) {
		BMI160_MSG_2(ERROR,
				"55555501 bmi160_init new dev I2C addr: 0x%X bus instance: 0x%X",
				device_info->port_config.bus_config.i2c->slave_addr,
				device_info->port_config.bus_instance);

		INSERT_TRACE_POINT(bmi160, 0x05);

#if !BMI160_CONFIG_RUN_ON_OSSC
		status = sns_ddf_open_port(&port_handle,
				&device_info->port_config);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		bmi160_sns_port_handle_singleton = port_handle;
#endif

		INSERT_TRACE_POINT(bmi160, 0x06);

		status = sns_ddf_malloc_ex((void**)&state,
				sizeof(sns_dd_bmi160_state_t), smgr_handle);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		INSERT_TRACE_POINT(bmi160, 0x07);
		BMI160_MSG_3_F(ERROR, "%d %p, %d",
				55555502, state, device_info->first_gpio);

		memset(state, 0, sizeof(sns_dd_bmi160_state_t));
		(*dd_handle_ptr) = (sns_ddf_handle_t)(&state->sub_dev[0]);

		status = bmi160_check_chip_id(port_handle, &state->chip_rev);
		if (SNS_DDF_SUCCESS != status) {
			sns_ddf_mfree_ex(state, smgr_handle);

#if !BMI160_CONFIG_RUN_ON_OSSC
			sns_ddf_close_port(port_handle);
#endif
			return status;
		}

		state->bps_data.bus_read       = bmi160_sbus_read_wrapper;
		state->bps_data.bus_write      = bmi160_sbus_write_wrapper;
		state->bps_data.udelay         = bmi160_udelay;
		state->bps_data.sbus_obj       = port_handle;

		state->port_handle = port_handle;
		state->sub_dev_cnt = 0;

		INSERT_TRACE_POINT_P(bmi160, state);
		INSERT_TRACE_POINT_P(bmi160, state->port_handle);

		//TODO: move afterwards
		state->next = bmi160_sns_dd_list_head.next;
		bmi160_sns_dd_list_head.next = state;
		sns_ddf_get_port_id(&device_info->port_config, &state->port_id);
		INSERT_TRACE_POINT(bmi160, 0x08);

		sns_dd_bmi160_prepare_caches(state);
		INSERT_TRACE_POINT(bmi160, 0x09);


		INSERT_TRACE_POINT(bmi160, 0x0a);
#if BMI160_CONFIG_ENABLE_MAG_IF
		struct bmi160_slave *slave_mag;
		BST_IGNORE_WARNING_UNUSED_VAR(slave_mag);

		slave_mag = state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG] =
			&BMI160_SLAVE_MAG_MODULE_SYMBOL;
#endif
		sensors_init = sns_ddf_memhandler_malloc_ex(memhandler,
				sizeof(sns_ddf_sensor_e) * BMI160_MAX_SENSORS_NUM,
				smgr_handle);

		// Check to see if valid input is given for num_sensors and sensors.
		// If not, then it is using the older version of SMGR (without using probe & SSI)
		if (0 == *num_sensors && SNS_DDF_SENSOR__NONE == *sensors[0]) {
			*num_sensors = 1;
			(*sensors)[0] = (sns_ddf_sensor_e)SNS_DDF_SENSOR_ACCEL;
			INSERT_TRACE_POINT(bmi160, 0xff);
		}

		sns_dd_bmi160_populate_hw_mod_list(state);
		// Fill out the first sub-device slot
		uint32_t num_sensors_init = sns_dd_bmi160_fill_sub_dev_slot(
				state,
				&state->sub_dev[0],
				smgr_handle,
				device_info->first_gpio,
				*num_sensors,
				*sensors,
				&sensors_init);

		BMI160_MSG_3_F(ERROR, "55555501 %d %d %p",
				num_sensors_init, *num_sensors,
				&state->sub_dev[state->sub_dev_cnt]);

		if (0 == num_sensors_init) {
			BMI160_MSG_0(ERROR, "bmi160_init - unable to initialize any sensors");
#if !BMI160_CONFIG_RUN_ON_OSSC
			sns_ddf_close_port(state->port_handle);
#endif
			sns_ddf_mfree_ex(state, smgr_handle);
			//this error is due to unrecoginized sensor types in the sensors param
			return SNS_DDF_EINVALID_PARAM;
		}
		INSERT_TRACE_POINT(bmi160, 0x0b);

		//(*dd_handle_ptr) = (sns_ddf_handle_t)(&state->sub_dev[0]);
		state->sub_dev_cnt++;
		sns_dd_bmi160_parse_nv_params(state, nv_params, *sensors);

		state->gpio1 = device_info->first_gpio;

		INSERT_TRACE_POINT(bmi160, 0x0c);
		//TODO: need two timers for accel and gyro seperately
		status = sns_ddf_timer_init(&state->bw_timer,
				(*dd_handle_ptr),
				&SNS_DD_IF_BMI160,
				state,
				0);

		status = sns_dd_bmi160_soft_reset_and_cfg_default(state);
		if (SNS_DDF_SUCCESS != status) {
#if !BMI160_CONFIG_RUN_ON_OSSC
			sns_ddf_close_port(state->port_handle);
#endif
			sns_ddf_mfree_ex(state, smgr_handle);
			return status;
		}

		INSERT_TRACE_POINT(bmi160, 0x0d);

		(*num_sensors) = num_sensors_init;
		(*sensors) = sensors_init;

		INSERT_TRACE_POINT_P(bmi160, *dd_handle_ptr);
		BMI160_MSG_3_F(HIGH, "[bmi160_if_init] succeeds for %p sensor_type: %d num_sensors: %d",
				*dd_handle_ptr, (*sensors)[0], *num_sensors);
		return SNS_DDF_SUCCESS;
	} else {
		BMI160_MSG_3_F(ERROR, "%d %d %d",
				55555501, state->sub_dev_cnt, 12345678);

		// If there is an empty slot
		if (state->sub_dev_cnt < BMI160_MAX_SUB_DEV_NUM) {
			// Assign the dd_handle_ptr
			//(*dd_handle_ptr) = (sns_ddf_handle_t) ((uint32_t) state | state->sub_dev_cnt);
			(*dd_handle_ptr) = (sns_ddf_handle_t)(&state->sub_dev[state->sub_dev_cnt]);

			sns_ddf_sensor_e        *sensors_init =
				sns_ddf_memhandler_malloc_ex(memhandler,
						sizeof(sns_ddf_sensor_e) * BMI160_MAX_SENSORS_NUM,
						smgr_handle);

			if (sensors_init == NULL) {
			   BMI160_MSG_0(ERROR, "bmi160_init - unable to initialize memory");
			   return SNS_DDF_ENOMEM;
			}

			// Fill out the next sub-device slot
			uint32_t num_sensors_init = sns_dd_bmi160_fill_sub_dev_slot(
					state,
					&state->sub_dev[state->sub_dev_cnt],
					smgr_handle,
					device_info->first_gpio,
					*num_sensors,
					*sensors,
					&sensors_init);

			BMI160_MSG_3_F(ERROR, "55555501 %d %d %p",
					num_sensors_init, *num_sensors,
					&state->sub_dev[state->sub_dev_cnt]);

			if (0 == num_sensors_init) {
				BMI160_MSG_0(ERROR, "bmi160_init - unable to initialize any sensors");
				return SNS_DDF_EINVALID_PARAM;
			}
			INSERT_TRACE_POINT(bmi160, 0x0e);

			(*num_sensors) = num_sensors_init;
			(*sensors) = sensors_init;
			BMI160_MSG_3(ERROR, "%d Finished initializing %u sensor(s). First sensor %u",
					55555501, *num_sensors, (*sensors)[0]);

			state->sub_dev_cnt++;
			BMI160_MSG_3_F(ERROR, "%d %d %d",
					55555504, state->sub_dev_cnt, 12345678);

			sns_dd_bmi160_parse_nv_params(state, nv_params, *sensors);
			INSERT_TRACE_POINT(bmi160, 0x0e);
			INSERT_TRACE_POINT_P(bmi160, *dd_handle_ptr);

			BMI160_MSG_3_F(HIGH, "[bmi160_if_init] succeeds for %p sensor_type: %d num_sensors: %d",
					*dd_handle_ptr, (*sensors)[0], *num_sensors);

			return SNS_DDF_SUCCESS;
		} else {
			return SNS_DDF_ENOMEM;
		}
	}

	return SNS_DDF_SUCCESS;
}
/*!
 *  @brief Sets an attribute of the bosch accelerometer
 *
 * @detail
 *  Called by SMGR to set certain device attributes that are
 *  programmable. Curently its the power mode and range.
 *
 *  @param[in] dd_handle   Handle to a driver instance.
 *  @param[in] sensor Sensor for which this attribute is to be set.
 *  @param[in] attrib      Attribute to be set.
 *  @param[in] value      Value to set this attribute.
 *
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS or
 *    SNS_DDF_EINVALID_PARAM
 *
 */
//reviewed
sns_ddf_status_e sns_dd_bmi160_set_attr(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_attribute_e     attrib,
		void                    *value)
{
	sns_ddf_status_e        status = SNS_DDF_SUCCESS;
	sns_dd_bmi160_state_t   *state;
	bmi160_sub_dev_t        *sub_dev;
	uint8_t                 n;

	BMI160_MSG_3_F(ERROR, "55555520 - <bmi160_if_ set_attrib> dd_handle: %p sensor_type: %d attrib: %d",
			dd_handle, sensor_type, attrib);
	INSERT_TRACE_POINT(bmi160, 0x20);

	if (dd_handle == NULL || value == NULL) {
		BMI160_MSG_0(ERROR, "55555521 NULL ptr got from SMGR");
		return SNS_DDF_EINVALID_PARAM;
	}

	sub_dev = sns_dd_bmi160_get_subdev(dd_handle);
	if (NULL == sub_dev) {
		return SNS_DDF_EINVALID_PARAM;
	}

	state = sns_dd_bmi160_get_dev(dd_handle);

	BMI160_MSG_3_F(ERROR, "55555521 dd_handle: %p state: %p sub_dev: %p",
			dd_handle, state, sub_dev);

	if (NULL == state) {
		BMI160_MSG_0(ERROR, "55555521 cannot figure out handle");
		return SNS_DDF_EINVALID_PARAM;
	}


	// If the requested sensor type is NONE, then do nothing
	if (SNS_DDF_SENSOR__NONE == sensor_type) {
		BMI160_MSG_3_F(ERROR, "%d 0x%x %d",
				55555521, 55555521, 55555521);
		return SNS_DDF_EINVALID_PARAM;
	}

	/* If the requested sensor type is ALL, then iterate through all of the
	 * sub-device's sensors and call this function with a specific sensor type */
	if (SNS_DDF_SENSOR__ALL == sensor_type) {
		BMI160_MSG_0(ERROR, "55555521 set attrib for all!");
		for (n = 0; n < sub_dev->num_sensors; n++) {
			status = sns_dd_bmi160_set_attr(dd_handle,
					sub_dev->sensors[n].sensor_type,
					attrib, value);

			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		}

		return SNS_DDF_SUCCESS;
	}

	INSERT_TRACE_POINT3(bmi160, 0x21, sensor_type, attrib);

	switch (attrib) {
		case SNS_DDF_ATTRIB_RANGE:
			status = sns_dd_bmi160_set_attr_range(
					state,
					sensor_type,
					value, 0);
			break;
		case SNS_DDF_ATTRIB_POWER_STATE:
			status = sns_dd_bmi160_set_attr_powerstate(
					state,
					sensor_type,
					value, 0);
			break;
		case SNS_DDF_ATTRIB_ODR:
			status = sns_dd_bmi160_set_attr_odr(state, sensor_type, value, 0);
			break;
#if BMI160_CONFIG_ENABLE_MD
		case SNS_DDF_ATTRIB_MOTION_DETECT:
			status = sns_dd_bmi160_set_attr_motion_detect(state,
					sensor_type,
					value, 0);
			break;
#endif

#if BMI160_CONFIG_ENABLE_FIFO
		case SNS_DDF_ATTRIB_FIFO:
			status = sns_dd_bmi160_set_attr_fifo(state,
					sensor_type,
					value, 0);
			break;
#endif

		case SNS_DDF_ATTRIB_LOWPASS:
#if 0   //REMOVE
			val_u8 = *((uint8_t *)value);
			if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
				if (val_u8 >= BST_ARRAY_SIZE(BMI160_ACC_BW_REGV_LIST)) {
					return SNS_DDF_EINVALID_ATTR;
				} else {
					state->odr_regv_acc = BMI160_ACC_BW_REGV_LIST[val_u8];
				}
				status = sns_dd_bmi160_cfg_hw_mod_acc_odr(state);
			} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
				if (val_u8  >= BST_ARRAY_SIZE(BMI160_GYR_BW_REGV_LIST)) {
					return SNS_DDF_EINVALID_ATTR;
				} else {
					state->odr_regv_gyr = BMI160_GYR_BW_REGV_LIST[val_u8];
				}
				status = sns_dd_bmi160_cfg_hw_mod_gyr_odr(state);
			} else {
				return SNS_DDF_EINVALID_PARAM;
			}

			break;
#else
			return SNS_DDF_EINVALID_ATTR;
#endif
		default:
			//return SNS_DDF_EINVALID_ATTR;
			//return SNS_DDF_SUCCESS;
			break;
	}

	INSERT_TRACE_POINT2(bmi160, 0x2f, status);

	if (SNS_DDF_SUCCESS == status) {
		BMI160_MSG_0(ERROR, "[bmi160_if_set_attrib] succeeds");
	}

	return status;
}

/*!
 *  @brief Called by the SMGR to retrieves the value of an attribute of
 *  the sensor.
 *
 *  @detail
 *  - range and resolution info is from the device data sheet.
 *
 *  @param[in]  dd_handle   Handle to a driver instance.
 *  @param[in] sensor       Sensor whose attribute is to be retrieved.
 *  @param[in]  attrib      Attribute to be retrieved.
 *  @param[in] memhandler  Memory handler used to dynamically allocate
 *                         output parameters, if applicable.
 *  @param[out] value      Pointer that this function will allocate or set
 *                         to the attribute's value.
 *  @param[out] num_elems  Number of elements in @a value.
 *
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
//reviewed
sns_ddf_status_e sns_dd_bmi160_get_attr(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_attribute_e     attrib,
		sns_ddf_memhandler_s    *memhandler,
		void                    **value,
		uint32_t                *num_elems)
{
	sns_dd_bmi160_state_t   *state;
	bmi160_sub_dev_t        *sub_dev;
	sns_ddf_status_e        status;

	BMI160_MSG_3_F(ERROR, "55555530 - <bmi160_if_ get_attrib> dd_handle: %p sensor_type: %d attrib: %d",
			dd_handle, sensor_type, attrib);

	INSERT_TRACE_POINT(bmi160, 0x30);

	sub_dev = sns_dd_bmi160_get_subdev(dd_handle);
	if (NULL == sub_dev) {
		return SNS_DDF_EINVALID_PARAM;
	}

	state = sns_dd_bmi160_get_dev(dd_handle);

	BMI160_MSG_3_F(ERROR, "55555531 dd_handle: %p state: %p sub_dev: %p",
			dd_handle, state, sub_dev);

	if (NULL == state) {
		BMI160_MSG_0(ERROR, "55555531 cannot figure out handle");
		return SNS_DDF_EINVALID_PARAM;
	}

	INSERT_TRACE_POINT3(bmi160, 0x31, sensor_type, attrib);

	switch (attrib) {
		case SNS_DDF_ATTRIB_POWER_INFO:
			{
				sns_ddf_power_info_s *power_attrib;
				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								sizeof(sns_ddf_power_info_s),
								sub_dev->smgr_handle)) == NULL)
				{
					return SNS_DDF_ENOMEM;
				}
				power_attrib = *value;

				switch (sensor_type) {
					case SNS_DDF_SENSOR_TEMP:
					case SNS_DDF_SENSOR_DOUBLETAP:
					case SNS_DDF_SENSOR_ACCEL:
						power_attrib->active_current    = 180;  // 180 uA
						power_attrib->lowpower_current  = 3;    // 3 uA
						break;
					case SNS_DDF_SENSOR_GYRO:
						power_attrib->active_current    = 900;  // 900 uA
						power_attrib->lowpower_current  = 3;    // 3 uA
						break;
#if BMI160_CONFIG_ENABLE_MAG_IF
					case SNS_DDF_SENSOR_MAG:
						{
							struct bmi160_slave *slave;

							slave = state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG] =
								&BMI160_SLAVE_MAG_MODULE_SYMBOL;

							power_attrib->active_current    = slave->current_ua_fullpower;
							power_attrib->lowpower_current  = slave->current_ua_lowpower;
						}
						break;
#endif
					default:
						return SNS_DDF_EINVALID_PARAM;
				}

				*num_elems = 1;
			}
			break;
		case SNS_DDF_ATTRIB_RANGE:
			{
				sns_ddf_range_s *device_ranges;

				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
									BST_ARRAY_SIZE(BMI160_ACC_RANGE_REGV_LIST) * sizeof(sns_ddf_range_s),
									sub_dev->smgr_handle))
							== NULL) {
						return SNS_DDF_ENOMEM;
					}
					device_ranges = *value;
					*num_elems = BST_ARRAY_SIZE(BMI160_ACC_RANGE_REGV_LIST);
					device_ranges[0].min = BOSCH_ACC_RANGE_2G_MIN;
					device_ranges[0].max = BOSCH_ACC_RANGE_2G_MAX;
					device_ranges[1].min = BOSCH_ACC_RANGE_4G_MIN;
					device_ranges[1].max = BOSCH_ACC_RANGE_4G_MAX;
					device_ranges[2].min = BOSCH_ACC_RANGE_8G_MIN;
					device_ranges[2].max = BOSCH_ACC_RANGE_8G_MAX;
					device_ranges[3].min = BOSCH_ACC_RANGE_16G_MIN;
					device_ranges[3].max = BOSCH_ACC_RANGE_16G_MAX;
				} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
									BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST) * sizeof(sns_ddf_range_s),
									sub_dev->smgr_handle))
							== NULL) {
						return SNS_DDF_ENOMEM;
					}
					device_ranges = *value;
					*num_elems = BST_ARRAY_SIZE(BMI160_GYR_RANGE_REGV_LIST);
					device_ranges[0].min = BOSCH_GYR_RANGE_125_MIN;
					device_ranges[0].max = BOSCH_GYR_RANGE_125_MAX;
					device_ranges[1].min = BOSCH_GYR_RANGE_250_MIN;
					device_ranges[1].max = BOSCH_GYR_RANGE_250_MAX;
					device_ranges[2].min = BOSCH_GYR_RANGE_500_MIN;
					device_ranges[2].max = BOSCH_GYR_RANGE_500_MAX;
					device_ranges[3].min = BOSCH_GYR_RANGE_1000_MIN;
					device_ranges[3].max = BOSCH_GYR_RANGE_1000_MAX;
					device_ranges[4].min = BOSCH_GYR_RANGE_2000_MIN;
					device_ranges[4].max = BOSCH_GYR_RANGE_2000_MAX;
				} else if (SNS_DDF_SENSOR_TEMP == sensor_type) {
					if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
									sizeof(sns_ddf_range_s),
									sub_dev->smgr_handle))
							== NULL) {
						return SNS_DDF_ENOMEM;
					}
					device_ranges = *value;
					*num_elems = 1;
					device_ranges->min = BOSCH_TEMP_MIN;
					device_ranges->max = BOSCH_TEMP_MAX;
#if BMI160_CONFIG_ENABLE_MAG_IF
				} else if (SNS_DDF_SENSOR_MAG == sensor_type) {
					//TODO: MAG
					if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
									sizeof(sns_ddf_range_s),
									sub_dev->smgr_handle))
							== NULL) {
						return SNS_DDF_ENOMEM;
					}
					device_ranges = *value;
					*num_elems = 1;
					device_ranges->min = FX_FLTTOFIX_Q16(-1200);
					device_ranges->max = FX_FLTTOFIX_Q16(2500);
#endif
				} else {
					//CHECK: following_ref_code_now
					return SNS_DDF_EINVALID_PARAM;
				}
			}
			break;
		case SNS_DDF_ATTRIB_RESOLUTION_ADC:
			{
				sns_ddf_resolution_adc_s *device_res;
				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								sizeof(sns_ddf_resolution_adc_s),
								sub_dev->smgr_handle))
						== NULL) {
					return SNS_DDF_ENOMEM;
				}

				device_res = *value;

				*num_elems = 1;
				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					device_res->bit_len = BMI160_ACC_BIT_LEN;
					device_res->max_freq = BMI160_CONFIG_ACC_MAX_FREQ;
				} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					device_res->bit_len = BMI160_GYR_BIT_LEN;
					device_res->max_freq = BMI160_CONFIG_GYR_MAX_FREQ;
				} else if (SNS_DDF_SENSOR_TEMP == sensor_type) {
					device_res->bit_len = BMI160_TEMP_BIT_LEN;
					device_res->max_freq = BMI160_CONFIG_TEMP_MAX_FREQ;
				}
				//NOTE:CRITICAL: if the max_freq is not filled properly
				//the SMGR does not interact with this driver later any more
				//CHECK: following_ref_code_now
				else if (SNS_DDF_SENSOR_DOUBLETAP == sensor_type) {
					device_res->bit_len = 8;
					device_res->max_freq = BMI160_CONFIG_DT_MAX_FREQ;
#if     BMI160_CONFIG_ENABLE_MAG_IF
				} else if (SNS_DDF_SENSOR_MAG == sensor_type) {
					//TODO: MAG
					device_res->bit_len = 16;
					device_res->max_freq = 100;
#endif
				} else {
					return SNS_DDF_EINVALID_PARAM;
				}

			}
			break;
		case SNS_DDF_ATTRIB_RESOLUTION:
			{
				sns_ddf_resolution_t *device_res;
				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								sizeof(sns_ddf_resolution_t),
								sub_dev->smgr_handle))
						== NULL)
				{
					return SNS_DDF_ENOMEM;
				}

				device_res = *value;

				*num_elems = 1;
				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					*device_res = FX_FLTTOFIX_Q16(G
							* (4 << state->range_idx_acc)
							/ (1 << BMI160_ACC_BIT_LEN));
				} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					*device_res = FX_FLTTOFIX_Q16(PI / 180
							* (250 << state->range_idx_gyr)
							/ (1 << BMI160_GYR_BIT_LEN));
				} else if (SNS_DDF_SENSOR_TEMP == sensor_type) {
					*device_res = FX_FLTTOFIX_Q16(1.0); /*! Degrees C */
				} else if (SNS_DDF_SENSOR_DOUBLETAP == sensor_type) {
					//CHECK: following_ref_code_now
					*device_res = 1;
				}
#if BMI160_CONFIG_ENABLE_MAG_IF
				else if (SNS_DDF_SENSOR_MAG == sensor_type) {
					struct bmi160_slave *slave;

					slave = state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG] =
						&BMI160_SLAVE_MAG_MODULE_SYMBOL;
					*device_res = FX_FLTTOFIX_Q16(slave->adc_resolution_milligauss * 0.001);
				}
#endif
			}
			break;
		case SNS_DDF_ATTRIB_LOWPASS:
#if 0   //REMOVE
			{
				uint8_t i;
				sns_ddf_lowpass_freq_t *freq_set;
				*num_elems = 8;
				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								(*num_elems)*sizeof(sns_ddf_lowpass_freq_t),
								sub_dev->smgr_handle))
						== NULL) {
					return SNS_DDF_ENOMEM;
				}
				freq_set = *value;

				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					*num_elems = 16;
					for (i = 0; i<*num_elems; i++) {
						*(freq_set+i) = BMI160_ACC_FREQ_LIST[i];
					}
				}

				else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					*num_elems = 8;
					for (i = 0; i<*num_elems; i++) {
						*(freq_set+i) = BMI160_GYR_FREQ_LIST[i];
					}
				}
			}
			break;
#else
			return SNS_DDF_EINVALID_ATTR;
#endif
		case SNS_DDF_ATTRIB_DELAYS:
			{
				sns_ddf_delays_s *device_delay;
				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								sizeof(sns_ddf_delays_s),
								sub_dev->smgr_handle))
						== NULL) {
					return SNS_DDF_ENOMEM;
				}
				device_delay = *value;
				*num_elems = 1;

				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					device_delay->time_to_active = 1000;
					//TODO
					device_delay->time_to_data = 160000;
				} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					device_delay->time_to_active = 40000;
					//TODO
					device_delay->time_to_data = 16000;
				} else {
					device_delay->time_to_active = 1000;
					//TODO
					device_delay->time_to_data = 10000;
				}
			}
			break;
		case SNS_DDF_ATTRIB_DRIVER_INFO:
			{
				BMI160_MSG_0(LOW, "Getting attribute DRIVER INFO");
				*value = &bmi160_sns_dd_list_head.dd_info;
				*num_elems = 1;
			}
			break;
		case SNS_DDF_ATTRIB_DEVICE_INFO:
			{
				sns_ddf_device_info_s *device_info;

				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								sizeof(sns_ddf_device_info_s),
								sub_dev->smgr_handle))
						== NULL) {
					return SNS_DDF_ENOMEM;
				}
				device_info = *value;
				*num_elems = 1;
				device_info->vendor = "BOSCH";
				device_info->model = "BMI160";

				switch (sensor_type) {
					case SNS_DDF_SENSOR_ACCEL:
						device_info->name = "Accelerometer";
						break;
					case SNS_DDF_SENSOR_GYRO:
						device_info->name = "Gyroscope";
						break;
					case SNS_DDF_SENSOR_DOUBLETAP:
						device_info->name = "DoubleTap";
						break;
					case SNS_DDF_SENSOR_TEMP:
						device_info->name = "Temperature";
						break;
#if BMI160_CONFIG_ENABLE_MAG_IF
					case SNS_DDF_SENSOR_MAG:
						{
							struct bmi160_slave *slave;
							slave = state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG] =
								&BMI160_SLAVE_MAG_MODULE_SYMBOL;

							if (NULL != slave->name) {
								device_info->name = (char *)slave->name;
							} else {
								device_info->name = "Magnetic";
							}
						}
						break;
#endif
					default:
						device_info->name = "Unknown";
						break;
				}

				device_info->version = 1;
			}
			break;
		case SNS_DDF_ATTRIB_IO_REGISTER:
			{
				sns_ddf_io_register_s *io_reg_in = (sns_ddf_io_register_s *)(*value);

				if ((unsigned long)(io_reg_in->address_ptr) > 0xFFFF)
				{
					return SNS_DDF_EINVALID_PARAM;
				}
				if (io_reg_in->length > 0xFF)
				{
					return SNS_DDF_EINVALID_PARAM;
				}

				// Allocate memory for the output data structure and for the data to be read from the register(s)
				sns_ddf_io_register_s *io_reg_out = sns_ddf_memhandler_malloc_ex(
						memhandler,
						sizeof(sns_ddf_io_register_s) + (sizeof(uint8_t) * (io_reg_in->length - 1)),
						sub_dev->smgr_handle);
				if (io_reg_out == NULL)
					return SNS_DDF_ENOMEM;

				status = bmi160_sbus_read_wrapper(
						state->port_handle,
						(uint16_t)((unsigned long)io_reg_in->address_ptr),
						&(io_reg_out->data[0]),
						(uint8_t)io_reg_in->length);
				BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

				// Fill out the information in the output io_register data structure
				io_reg_out->address_ptr = io_reg_in->address_ptr;
				io_reg_out->addr_fixed = io_reg_in->addr_fixed;
				io_reg_out->data_width = io_reg_in->data_width;
				io_reg_out->length = io_reg_in->length;
				// Return the io_register data structure by reference
				*value = io_reg_out;
				*num_elems = 1;
			}
			break;
		case SNS_DDF_ATTRIB_BIAS:
			{
				if ((*value = sns_ddf_memhandler_malloc_ex(memhandler,
								sizeof(sns_dd_bmi160_state_t),
								sub_dev->smgr_handle))
						== NULL)

				{
					return SNS_DDF_ENOMEM;
				}

				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					*value = state->bias_acc;
					*num_elems = 3;
					return SNS_DDF_SUCCESS;
				} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					*value = state->bias_gyr;
					*num_elems = 3;
					return SNS_DDF_SUCCESS;
#if BMI160_CONFIG_ENABLE_MAG_IF
				} else if (SNS_DDF_SENSOR_MAG == sensor_type) {
#endif
				} else {
					return SNS_DDF_EINVALID_PARAM;
				}
			}
		case SNS_DDF_ATTRIB_ODR:
			{
				status = sns_dd_bmi160_get_attr_odr(state, sensor_type,
						memhandler, value, num_elems, 0);
				BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
			}
			break;

		case SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST:
			{
				uint32_t *odr_list;
				uint8_t i;
				uint16_t odr_max;
				uint16_t idx_odr_max;

				switch (sensor_type) {
					case SNS_DDF_SENSOR_ACCEL:
						odr_max = BMI160_CONFIG_ACC_FASTEST_ODR;
						break;
					case SNS_DDF_SENSOR_GYRO:
						odr_max = BMI160_CONFIG_GYR_FASTEST_ODR;
						break;
					case SNS_DDF_SENSOR_MAG:
						odr_max = BMI160_CONFIG_MAG_FASTEST_ODR;
						break;
					case SNS_DDF_SENSOR_TEMP:
						odr_max = BMI160_CONFIG_TEMP_FASTEST_ODR;
						break;
					case SNS_DDF_SENSOR_DOUBLETAP:
						odr_max = BMI160_CONFIG_DT_FASTEST_ODR;
						break;
					default:
						return SNS_DDF_EINVALID_PARAM;
				}

				idx_odr_max = BST_ARRAY_SIZE(BMI160_REGV_ODR_MAP) - 1;
				for (i = 0; i < BST_ARRAY_SIZE(BMI160_REGV_ODR_MAP); i++) {
					if (BMI160_REGV_ODR_MAP[i].l >= odr_max) {
						idx_odr_max = i;
						break;
					}
				}

				odr_list = sns_ddf_memhandler_malloc_ex(memhandler,
						sizeof(odr_list[0]) * (idx_odr_max + 1),
						sub_dev->smgr_handle);
				if (!odr_list) {
					BMI160_MSG_0(ERROR, "No memory for SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST");
					return SNS_DDF_ENOMEM;
				}

				for (i = 0; i < idx_odr_max + 1; i++) {
					odr_list[i] = BMI160_REGV_ODR_MAP[i].l;
				}

				*value = odr_list;
				*num_elems = i;
			}
			break;
#if BMI160_CONFIG_ENABLE_FIFO
		case SNS_DDF_ATTRIB_FIFO:
			{
				uint32_t i      = 0;
				uint32_t cnt    = 0;
				sns_ddf_fifo_attrib_get_s *fifo_attr = NULL;
				bmi160_sub_dev_t *sub_dev_tmp;
				uint32_t         size_attr;

				size_attr = sizeof(sns_ddf_fifo_attrib_get_s) +
					(BST_ARRAY_SIZE(BMI160_FIFO_SENSOR_LIST) - 2) * sizeof(sns_ddf_fifo_share_sensor_s *);

				fifo_attr = sns_ddf_memhandler_malloc_ex(memhandler, size_attr, sub_dev->smgr_handle);

				if (NULL == fifo_attr) {
					BMI160_MSG_0(ERROR, "No memory for fifo_attr");
					return SNS_DDF_ENOMEM;
				}

				fifo_attr->is_supported         =  true;
				fifo_attr->is_sw_watermark      =  false;
				fifo_attr->share_sensor_cnt     =  0;

				if (SNS_DDF_SENSOR_ACCEL == sensor_type) {
					fifo_attr->max_watermark =  BMI160_FF_MAX_LEVEL_ACC;
				} else if (SNS_DDF_SENSOR_GYRO == sensor_type) {
					fifo_attr->max_watermark =  BMI160_FF_MAX_LEVEL_GYR;
				} else if (SNS_DDF_SENSOR_MAG == sensor_type) {
					fifo_attr->max_watermark =  BMI160_FF_MAX_LEVEL_MAG;
				}

				size_attr = sizeof(sns_ddf_fifo_share_sensor_s);

				for (i = 0; i < BST_ARRAY_SIZE(BMI160_FIFO_SENSOR_LIST) - 1; i++) {
					fifo_attr->share_sensors[i] = sns_ddf_memhandler_malloc_ex(memhandler, size_attr, sub_dev->smgr_handle);
					if (fifo_attr->share_sensors[i] == NULL) {
						BMI160_MSG_1(ERROR, "No memory for share_sensors[%d]", i);
						return SNS_DDF_ENOMEM;
					}
				}


				BMI160_MSG_2(MED, "SNS_DDF_ATTRIB_FIFO: sensor_type = %u max_watermark = %u",
						sensor_type, fifo_attr->max_watermark);

				cnt = 0;
				for (i = 0; i < BST_ARRAY_SIZE(BMI160_FIFO_SENSOR_LIST); i++) {
					if (sensor_type != BMI160_FIFO_SENSOR_LIST[i]) {
						sub_dev_tmp = sns_dd_bmi160_get_subdev_from_type(state,
								BMI160_FIFO_SENSOR_LIST[i]);
						if (sub_dev_tmp && sub_dev_tmp->smgr_handle) {
							fifo_attr->share_sensors[cnt]->sensor = BMI160_FIFO_SENSOR_LIST[i];
							fifo_attr->share_sensors[cnt]->dd_handle = sub_dev_tmp->smgr_handle;

							BMI160_MSG_2(MED, "SNS_DDF_ATTRIB_FIFO shared sensor %u handle=%p",
									fifo_attr->share_sensors[cnt]->sensor,
									fifo_attr->share_sensors[cnt]->dd_handle);

							cnt++;
						}
					}
				}

				fifo_attr->share_sensor_cnt = cnt;
				*value = fifo_attr;
				*num_elems = 1;
			}
			break;
#endif

		default:
			return SNS_DDF_EINVALID_ATTR;
	}

	INSERT_TRACE_POINT(bmi160, 0x3f);

	BMI160_MSG_0(ERROR, "[bmi160_if_get_attrib] succeeds");

	return SNS_DDF_SUCCESS;
}
/*!
 *  @brief Resets the driver and device so they return to the state they were
 *         in after init() was called.
 *
 *  @detail
 *   resets the bias to zero & range to 2G which
 *   is stored in the driver state structure
 *
 *  @param[in] state: Ptr to the driver structure
 *
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
sns_ddf_status_e sns_dd_bmi160_reset(sns_ddf_handle_t dd_handle)
{
	bmi160_sub_dev_t        *sub_dev = sns_dd_bmi160_get_subdev(dd_handle);
	sns_ddf_sensor_e        sensor_type;
	sns_dd_bmi160_state_t   *state = sns_dd_bmi160_get_dev(dd_handle);
	uint8_t                 si_buf_rd[2] = "";

	sensor_type = sub_dev->sensors[0].sensor_type;

	BST_IGNORE_WARNING_UNUSED_VAR(sensor_type);

	BMI160_MSG_3_F(ERROR, "55555560 - <bmi160_if_ reset> dd_handle: %p sensor_type: %d %d",
			dd_handle, sensor_type, 0);

	BMI160_MSG_2(ERROR, "55555560 - [bmi160_if_reset] us_2_ticks: %d ms_2_ticks: %d",
			BMI160_SSC_US_2_TICKS(1000000), BMI160_SSC_US_2_TICKS(1000));


	INSERT_TRACE_POINT(bmi160, 0x60);

	INSERT_TRACE_POINT_T(bmi160, 0x60 + sub_dev->sensors[0].sensor_type);


	bmi160_sbus_read_wrapper(
			state->port_handle,
			BMI160_REGA_USR_CHIP_ID,
			si_buf_rd,
			1);
	bmi160_udelay(BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);

	if (BMI160_REGV_CHIP_ID_MAJOR != (si_buf_rd[0] & BMI160_REGV_CHIP_ID_MAJOR)) {
		bmi160_sbus_read_wrapper(
				state->port_handle,
				BMI160_REGA_USR_CHIP_ID,
				si_buf_rd,
				1);
		bmi160_udelay(BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US);
	}

	//we don't need to do anything particular, because the sensor comes in SUSPEND mode at POR
#if 0
	bool                    reset;
	reset = false;
	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			if (0 == state->odr_dbt_req) {
				reset = true;
			}
			break;
		case SNS_DDF_SENSOR_GYRO:
		case SNS_DDF_SENSOR_MAG:
			reset = true;
			break;
		default:
			reset = false;
	}

	if (reset) {
		sns_dd_bmi160_reset_state(state, sensor_type, 0);
	}
#endif

	BMI160_MSG_0(ERROR, "[bmi160_if_reset] succeeds");
	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_bmi160_self_test(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_test_e          test_type,
		uint32_t                *err)
{
	sns_ddf_status_e        status;
	sns_dd_bmi160_state_t   *state = sns_dd_bmi160_get_dev(dd_handle);
	int32_t                 caller = ('t' << 8);

	BMI160_MSG_3_F(ERROR, "55555570 - <bmi160_if_ self_test> dd_handle: %p sensor_type: %d test_type: %d",
			dd_handle, sensor_type, test_type);

	if (!state) {
		return SNS_DDF_EINVALID_PARAM;
	}

	if (state->odr_acc_req || state->odr_gyr_req || state->odr_mag_req) {
		BMI160_MSG_3_F(ERROR,
				"55555571 - [self_test] WARNING!!! some client is still using the sensor, "
				"suggest to close it before doing the selftest, "
				"self test conflicts with data streaming functions, "
				"acc_odr_req: 0x%x gyr_odr_req: %d mag_odr_req: %d",
				state->odr_acc_req, state->odr_gyr_req, state->odr_mag_req);

		return SNS_DDF_EDEVICE_BUSY;
	}

	*err = 0;

	switch (test_type) {
		case SNS_DDF_TEST_SELF:
		case SNS_DDF_TEST_CONNECTIVITY:
			status = sns_dd_bmi160_run_test_self(state, sensor_type, err);
			break;
#if BMI160_CONFIG_ENABLE_SELFTEST
		case SNS_DDF_TEST_OEM:
			status = sns_dd_bmi160_run_test_oem(dd_handle, sensor_type, err);
			break;
		case SNS_DDF_TEST_SELF_HW:
		case SNS_DDF_TEST_SELF_SW:
			status = sns_dd_bmi160_run_test_sw_hw(state, sensor_type, err);
			BMI160_MSG_1(ERROR,
					"[self_test] call the reset function for: %d", sensor_type);
			caller |= 'w';
			sns_dd_bmi160_reset_state(state, sensor_type, caller);
			break;
		case SNS_DDF_TEST_IRQ:
			{
				bool signal_registered = state->signal_registered;
				status = sns_dd_bmi160_run_test_irq(state, sensor_type, err);
				caller |= 'i';
				sns_dd_bmi160_reset_state(state, sensor_type, caller);
				state->signal_registered = signal_registered;
			}
			break;
#endif
		default:
			return SNS_DDF_EINVALID_TEST;
	}

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	*err = 0;
	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e sns_dd_bmi160_probe(
		sns_ddf_device_access_s *device_info,
		sns_ddf_memhandler_s    *memhandler,
		uint32_t                *num_sensors,
		sns_ddf_sensor_e        **sensors)
{
	sns_ddf_status_e        status;
	sns_ddf_handle_t        port_handle;
	uint16_t                chip_rev;

	*num_sensors = 0;
	*sensors = NULL;

	BMI160_MSG_3_F(ERROR, "55555590 *num_sensors: %d %d %c",
			*num_sensors, 12345678, 'p');

	status = sns_ddf_open_port(&port_handle, &(device_info->port_config));
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	status = bmi160_check_chip_id(port_handle, &chip_rev);
#if !BMI160_CONFIG_RUN_ON_OSSC
	sns_ddf_close_port(port_handle);
#endif
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);


#if BMI160_CONFIG_ENABLE_MAG_IF
	*num_sensors = 5;
#else
	*num_sensors = 4;
#endif
	*sensors = sns_ddf_memhandler_malloc(memhandler,
			sizeof(sns_ddf_sensor_e) * (*num_sensors));
	if (*sensors != NULL) {
		(*sensors)[0] = SNS_DDF_SENSOR_ACCEL;
		(*sensors)[1] = SNS_DDF_SENSOR_TEMP;
		(*sensors)[2] = SNS_DDF_SENSOR_GYRO;
		(*sensors)[3] = SNS_DDF_SENSOR_DOUBLETAP;
#if BMI160_CONFIG_ENABLE_MAG_IF
		(*sensors)[4] = SNS_DDF_SENSOR_MAG;
#endif
		status = SNS_DDF_SUCCESS;
	} else {
		status = SNS_DDF_ENOMEM;
	}

	if (SNS_DDF_SUCCESS == status) {
		BMI160_MSG_0(ERROR, "[bmi160_if_probe] succeeds");
	}

	return status;
}

sns_ddf_status_e sns_dd_bmi160_enable_sched_data(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		bool                    enable)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	sns_dd_bmi160_state_t *state = sns_dd_bmi160_get_dev(dd_handle);

	BMI160_MSG_3_F(ERROR, "55555580 - <bmi160_if_ enable_sched_data> sensor_type: %d enable: %d ff_wml: %d",
			sensor_type, enable, state->ff_wml);
	INSERT_TRACE_POINT4_T(bmi160, 0x80, sensor_type, enable, state->ff_wml);

	BMI160_MSG_4(HIGH,
			"[dump_core_reg] enter en_int_drdy: 0x%x en_int_fifo: 0x%x en_int_md: %d en_int_dbt: %d",
			state->int_en_flags.bits.drdy.flag,
			state->int_en_flags.bits.fifo.flag,
			state->int_en_flags.bits.md,
			state->int_en_flags.bits.dt);

	BMI160_MSG_3(HIGH,
			"[dump_core_reg] en_int_drdy_agm: %d %d %d",
			state->int_en_flags.bits.drdy.bits.acc,
			state->int_en_flags.bits.drdy.bits.gyr,
			state->int_en_flags.bits.drdy.bits.mag);

	BMI160_MSG_3(HIGH,
			"[dump_core_reg] en_int_fifo_agm: %d %d %d",
			state->int_en_flags.bits.fifo.bits.acc,
			state->int_en_flags.bits.fifo.bits.gyr,
			state->int_en_flags.bits.fifo.bits.mag);

	if (!sns_ddf_signal_irq_enabled()) {
		return SNS_DDF_EINVALID_PARAM;
	}

	if (enable) {
		status = sns_dd_bmi160_signal_register(state);
	}
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
		case SNS_DDF_SENSOR_GYRO:
		case SNS_DDF_SENSOR_MAG:
			status = sns_dd_bmi160_enable_sched_data_agm(state,
					sensor_type, enable);
			break;
		case SNS_DDF_SENSOR_DOUBLETAP:
			//we already enabled interrupts for double tap in the set_attr_odr()
			status = SNS_DDF_SUCCESS;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	if (state->int_en_flags.bits.fifo.flag) {
		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_INT_MAP_1,
				&state->regv_int_map_1, 1);

		if (SNS_DDF_SUCCESS != status) {
			state->regv_int_map_1 = 0;
			state->regv_int_map_1 = BST_SET_VAL_BIT(state->regv_int_map_1, 6);
		}

		BMI160_MSG_1(HIGH,
				"enable_sched_data regv_int_map_1: 0x%x",
				state->regv_int_map_1);
	}

	BMI160_MSG_4(HIGH,
			"[dump_core_reg] exit  en_int_drdy: 0x%x en_int_fifo: 0x%x en_int_md: %d en_int_dbt: %d",
			state->int_en_flags.bits.drdy.flag,
			state->int_en_flags.bits.fifo.flag,
			state->int_en_flags.bits.md,
			state->int_en_flags.bits.dt);

	if (!enable) {
		status = sns_dd_bmi160_signal_deregister(state);
	}

	bmi160_dump_core_reg(state->port_handle);

	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

