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


#include "sns_dd_bmi160.h"
#include "sns_dd_bmi160_priv.h"

sns_ddf_driver_if_s SNS_DD_IF_BMI160;

sns_ddf_handle_t bmi160_sns_port_handle_singleton = NULL;

const double BMI160_SCALE_FACTOR_ACC_PM2G = (4 * G) / 65536;
const double BMI160_SCALE_FACTOR_GYR_PM125DPS = (250 * PI) / 180 / 65536;
const double BMI160_SCALE_FACTOR_TEMP = 1.0 / 512;
/*! function implementations */


/*! make sure the return value from sns_ddf_read_port is pass through
 *  as other code will check against some return values
 */
int32_t bmi160_sbus_read_wrapper(
		void                    *plat_obj,
		uint8_t                 reg_addr,
		uint8_t                 *buf,
		uint32_t                len)
{
	sns_ddf_status_e        status;
	sns_ddf_handle_t port_handle  = (sns_ddf_handle_t)plat_obj;

	if (len < 1) {
		return SNS_DDF_EINVALID_PARAM;
	}

#if BMI160_CONFIG_SBUS_USE_SPI
	uint8_t si_buf_wr[1] = {reg_addr};
	uint32_t out32;

	status = sns_ddf_spi_data_transfer(
			port_handle,
			buf,
			len,
			si_buf_wr,
			1,
			&out32);

	return status;
#else
	uint8_t out_wrapper;

	status = sns_ddf_read_port(
			port_handle,
			reg_addr,
			buf,
			len,
			&out_wrapper);
	if (1 != len) {
	} else {
		BMI160_MSG_4(HIGH, "<sbus_read> <@0x%02x : 0x%02x len: %d status: %d>",
				reg_addr, buf[0], len, status);
	}
	return status;
#endif
}

/*! make sure the return value from sns_ddf_write_port is pass through
 *  as other code will check against some return values
 */
#if BMI160_CONFIG_SBUS_USE_SPI
uint8_t g_spi_buf_wr[16];
#endif
int32_t bmi160_sbus_write_wrapper(
		void                    *plat_obj,
		uint8_t                 reg_addr,
		uint8_t                 *buf,
		uint32_t                len)
{
	sns_ddf_status_e status;

	sns_ddf_handle_t port_handle  = (sns_ddf_handle_t)plat_obj;

	if (len < 1) {
		return SNS_DDF_EINVALID_PARAM;
	}
#if BMI160_CONFIG_SBUS_USE_SPI
	uint32_t out32;
	g_spi_buf_wr[0] = reg_addr;
	memcpy(g_spi_buf_wr + 1, buf, len);
	status = sns_ddf_spi_data_transfer(
			port_handle,
			NULL,
			0,
			g_spi_buf_wr,
			len,
			&out32);

	return status;
#else
	uint8_t out;
	status = sns_ddf_write_port(port_handle,
			reg_addr,
			buf,
			len,
			&out);
#endif
	sns_ddf_delay(BMI160_SPEC_IF_IDLE_TIME_NORMAL_US + 10);
	BMI160_MSG_4(HIGH, "<sbus_write> <@0x%02x : 0x%02x len: %d status: %d>",
			reg_addr, buf[0], len, status);

	return status;
}

#if 0
int32_t bmi160_sbus_reg_rcu_bit_blk_val(
		void    *plat_obj,
		uint8_t reg_addr,
		uint8_t bit_start,
		uint8_t bit_end,
		uint8_t val_bit_blk)
{
	int32_t err;
	uint8_t regv;

	err = bmi160_sbus_read_wrapper(
			plat_obj,
			reg_addr,
			&regv,
			1);

	BMI160_DD_CHECK_RETVAL(err, SNS_DDF_SUCCESS);

	regv = BST_SET_VAL_BITBLOCK(regv, bit_start, bit_end, val_bit_blk);
	err = bmi160_sbus_write_wrapper(
			plat_obj,
			reg_addr,
			&regv,
			1);
	BMI160_DD_CHECK_RETVAL(err, SNS_DDF_SUCCESS);

	return 0;
}
#endif

//reviewed
void bmi160_parse_data_acc(
		uint8_t                 *buf,
		uint8_t                 len,
		struct bmi160_val_acc   *val)
{
	val->x = (buf[1] << 8) | (buf[0]);
	val->y = (buf[3] << 8) | (buf[2]);
	val->z = (buf[5] << 8) | (buf[4]);
}

//reviewed
static void bmi160_parse_data_ts(
		uint8_t                 *buf,
		uint8_t                 len,
		uint32_t                *ts_hw)
{
	*ts_hw = ((buf[2] << 16)
			| (buf[1] << 8)
			| (buf[0]));
}

//reviewed
static void bmi160_parse_data_gyr(
		uint8_t                 *buf,
		uint8_t                 len,
		struct bmi160_val_gyr   *val)
{
	val->x = (buf[1] << 8) | (buf[0]);
	val->y = (buf[3] << 8) | (buf[2]);
	val->z = (buf[5] << 8) | (buf[4]);
}

void bmi160_parse_reg_status(
		uint8_t                 regv_status,
		bmi160_status_reg_t     *stat_reg)
{
	stat_reg->bits.drdy_acc = BST_GET_VAL_BIT(regv_status, 7);
	stat_reg->bits.drdy_gyr = BST_GET_VAL_BIT(regv_status, 6);
	stat_reg->bits.drdy_mag = BST_GET_VAL_BIT(regv_status, 5);
}

#if BMI160_CONFIG_ENABLE_INT_DOUBLE_TAP
/*!
 *  @brief
 *  @return
 *  Available values
 *  0x00: none
 *  0x10: x,
 *  0x20: y,
 *  0x40: z
 */
//reviewed
int32_t bmi160_get_tap_first(uint8_t int_stat)
{
	int8_t first_x;
	int8_t first_y;
	int8_t first_z;

	first_x = BST_GET_VAL_BIT(int_stat, 4);
	first_y = BST_GET_VAL_BIT(int_stat, 5);
	first_z = BST_GET_VAL_BIT(int_stat, 6);

	//this code have preference as: z->y->x
	if (first_z) {
		return BMI160_INT_INFO_TAP_FIRST_Z;
	}

	if (first_y) {
		return BMI160_INT_INFO_TAP_FIRST_Y;
	}

	if (first_x) {
		return BMI160_INT_INFO_TAP_FIRST_X;
	}

	return BMI160_INT_INFO_TAP_FIRST_NONE;
}

#endif

sns_ddf_status_e bmi160_get_reg_ts_hw(
		sns_ddf_handle_t        port_handle,
		uint32_t                *ts_hw)
{
	sns_ddf_status_e status;
	uint8_t si_buf_rd[3];

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_SENSORTIME_0, si_buf_rd, 3);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	bmi160_parse_data_ts(si_buf_rd, 3, ts_hw);

	return SNS_DDF_SUCCESS;
}

uint32_t bmi160_get_ts_dev_update_msb(
		uint32_t start,
		uint32_t end,
		uint8_t  lsb_bits)
{
	uint32_t mask = ~((1 << lsb_bits) - 1);
	uint32_t ret;

	start &= mask;
	end &= mask;

	if (end >= start) {
		ret = (end - start) >> lsb_bits;
	} else {
		ret = (BMI160_TS_LSB_OVERFLOW_VAL - start + end) >> lsb_bits;
	}

	return ret;
}

//reviewed
sns_ddf_status_e bmi160_get_reg_hw_err_stat(
		sns_ddf_handle_t                port_handle,
		union bmi160_hw_err_stat        *hw_err_st)
{
	sns_ddf_status_e status;
	uint8_t si_buf_rd;

	status = bmi160_sbus_read_wrapper(
			port_handle,
			BMI160_REGA_USR_ERR_REG,
			&si_buf_rd,
			1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	hw_err_st->bits.mag_drdy_err    = BST_GET_VAL_BITBLOCK(si_buf_rd, 7, 7);
	hw_err_st->bits.drop_cmd_err    = BST_GET_VAL_BITBLOCK(si_buf_rd, 6, 6);
	hw_err_st->bits.i2c_fail_err    = BST_GET_VAL_BITBLOCK(si_buf_rd, 5, 5);
	hw_err_st->bits.err_code        = BST_GET_VAL_BITBLOCK(si_buf_rd, 1, 4);
	hw_err_st->bits.fatal_err       = BST_GET_VAL_BITBLOCK(si_buf_rd, 0, 0);

	if (hw_err_st->regv) {
		BMI160_MSG_3_F(ERROR, "WARNING!!! hw_err_st: 0x%x %d %d",
				hw_err_st->regv,
				hw_err_st->bits.fatal_err,
				hw_err_st->bits.err_code);

		BMI160_MSG_3_F(ERROR, "WARNING!!! hw_err_st: 0x%x %d %d",
				hw_err_st->bits.mag_drdy_err,
				hw_err_st->bits.drop_cmd_err,
				hw_err_st->bits.i2c_fail_err);
	}

	return SNS_DDF_SUCCESS;
}

sns_ddf_status_e bmi160_get_reg_fifo_count(
		sns_ddf_handle_t                port_handle,
		uint16_t                        *fifo_cnt)
{
	sns_ddf_status_e status;
	uint8_t si_buf[2] = "";

	status = bmi160_sbus_read_wrapper(port_handle,
			BMI160_REGA_USR_FIFO_LENGTH_0,
			si_buf, 2);

	*fifo_cnt = ((si_buf[1] & 0x07) << 8) | si_buf[0];

	return status;
}

//reviewing
sns_ddf_status_e bmi160_set_reg_int_map(
		sns_ddf_handle_t                port_handle,
		enum BMI160_INT_MAP_REG_NUM     map_num,
		uint8_t                         bit,
		bool                            enable)
{
	sns_ddf_status_e status;
	uint8_t si_buf;
	uint8_t rega;


	if (bit > 7) {
		return SNS_DDF_EINVALID_PARAM;
	}

	switch (map_num) {
		case BMI160_INT_MAP_REG_NUM0:
			rega = BMI160_REGA_USR_INT_MAP_0;
			break;
		case BMI160_INT_MAP_REG_NUM1:
			rega = BMI160_REGA_USR_INT_MAP_1;
			break;
		case BMI160_INT_MAP_REG_NUM2:
			rega = BMI160_REGA_USR_INT_MAP_2;
			break;
		default:
			return SNS_DDF_EINVALID_PARAM;
	}

	status = bmi160_sbus_read_wrapper(port_handle,
			rega,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (enable) {
		si_buf = BST_SET_VAL_BIT(si_buf, bit);
	} else {
		si_buf = BST_CLR_VAL_BIT(si_buf, bit);
	}

	status = bmi160_sbus_write_wrapper(port_handle,
			rega,
			&si_buf, 1);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	return SNS_DDF_SUCCESS;
}

//reviewed
static inline sns_ddf_status_e bmi160_reset_int(void    *plat_obj)
{
	sns_ddf_status_e status;
	sns_ddf_handle_t port_handle = (sns_ddf_handle_t)plat_obj;
	uint8_t si_buf_wr = BMI160_REGV_CMD_INT_RESET;

	status = bmi160_sbus_write_wrapper(port_handle,
			BMI160_REGA_CMD_CMD, &si_buf_wr, 1);

	return status;
}


//reviewed
sns_ddf_status_e bmi160_read_fifo_bytes(
		sns_ddf_handle_t port_handle,
		uint8_t *data,
		uint32_t len,
		uint32_t *out)
{
#if BMI160_CONFIG_ENABLE_FIFO
	sns_ddf_status_e status;

	status = sns_ddf_read_port_u32_count(port_handle,
			BMI160_REGA_USR_FIFO_DATA,
			data,
			len,
			out);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
#endif
	return SNS_DDF_SUCCESS;
}


int32_t bmi160_read_reg_int_ctx(
		void                            *plat_obj,
		bmi160_int_en_flag_t            *int_en_flags,
		struct bmi160_reg_int_context   *ctx)
{
	int32_t err;
	sns_ddf_handle_t port_handle = (sns_ddf_handle_t)plat_obj;
	int8_t reg_addr_start = -1;
	int8_t reg_addr_end = -1;
	int8_t len = 0;
	uint8_t si_buf_rd[9] = "";

	sns_ddf_time_t t1;
	sns_ddf_time_t t2;

	ctx->avail.flags = 0;
	//always include ts
	reg_addr_start = BMI160_REGA_USR_SENSORTIME_0;
	ctx->avail.bits.ts = 1;

	ctx->avail.bits.status_0 = 1;
	ctx->avail.bits.status_1 = 1;
	if (!int_en_flags->bits.dt) {
		reg_addr_end = BMI160_REGA_USR_INT_STATUS_1;
	} else {
		reg_addr_end = BMI160_REGA_USR_INT_STATUS_2;
		ctx->avail.bits.status_2 = 1;
	}

	len = reg_addr_end - reg_addr_start + 1;
	if ((len > 0) && (len <= BST_ARRAY_SIZE(si_buf_rd))) {

		t1 = sns_ddf_get_timestamp();
		err = bmi160_sbus_read_wrapper(port_handle,
				reg_addr_start, si_buf_rd, len);
		t2 = bmi160_get_sys_tick();

		ctx->ts_sys = t1 + (sns_dd_bmi160_get_time_elapse_sys(t1, t2) / 2);

		BMI160_DD_CHECK_RETVAL(err, 0);

		bmi160_parse_data_ts(si_buf_rd, 3, &ctx->ts_hw);

		ctx->status    = si_buf_rd[3];
		ctx->int_status_0 = si_buf_rd[4];
		ctx->int_status_1 = si_buf_rd[5];
		ctx->int_status_2 = si_buf_rd[6];
	} else {
		return SNS_DDF_EINVALID_PARAM;
	}

	return 0;
}

inline void bmi160_parse_int_stat_flags(
		struct bmi160_reg_int_context   *ctx,
		bmi160_int_stat_flag_t          *int_stat)
{
	int_stat->bits.md       = BST_GET_VAL_BIT(ctx->int_status_0, 2);
	int_stat->bits.dt       = BST_GET_VAL_BIT(ctx->int_status_0, 4);

	int_stat->bits.drdy     = BST_GET_VAL_BIT(ctx->int_status_1, 4);
	int_stat->bits.ff_full  = BST_GET_VAL_BIT(ctx->int_status_1, 5);
	int_stat->bits.ff_wml   = BST_GET_VAL_BIT(ctx->int_status_1, 6);
}

//reviewing
static sns_ddf_status_e bmi160_read_data(
		sns_ddf_handle_t                        port_handle,
		struct bmi160_sensor_data_raw_buf       *data,
		union bmi160_sensor_data_req            *req)
{
	sns_ddf_status_e        status = SNS_DDF_SUCCESS;
	uint8_t                 len;
	uint8_t                 idx;
	uint8_t                 reg_addr_start;
	uint8_t                 reg_addr_end;
	uint8_t                 si_buf_rd[32] = "";

	//read data a, g, m firstly, then temperature
	reg_addr_start = 0;
	reg_addr_end = 0;

	if (req->bits.m) {
		reg_addr_start  = BMI160_REGA_USR_DATA_0;
		reg_addr_end    = BMI160_REGA_USR_DATA_7;
	}

	if (req->bits.g) {
		if (0 == reg_addr_start) {
			reg_addr_start  = BMI160_REGA_USR_DATA_8;
		}
		reg_addr_end    = BMI160_REGA_USR_DATA_13;
	}

	if (req->bits.a) {
		if (0 == reg_addr_start) {
			reg_addr_start  = BMI160_REGA_USR_DATA_14;
		}
		reg_addr_end    = BMI160_REGA_USR_DATA_19;
	}

	if (req->bits.ts) {
		if (0 == reg_addr_start) {
			reg_addr_start  = BMI160_REGA_USR_SENSORTIME_0;
		}
		reg_addr_end    = BMI160_REGA_USR_SENSORTIME_2;
	}

	//we want to do a burst read of data and time together
	//for accuracy and sync of time

	if ((reg_addr_start> 0) && (reg_addr_end >= reg_addr_start)) {
		len = reg_addr_end - reg_addr_start + 1;
	} else {
		len = 0;
	}

	if (len > 0) {
		status = bmi160_sbus_read_wrapper(port_handle,
				reg_addr_start,
				si_buf_rd,
				len);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	}

	idx = 0;

	if (req->bits.m) {
#if BMI160_CONFIG_ENABLE_MAG_IF
		memcpy(data->buf_m, si_buf_rd + idx, 8);
#endif
		idx += 8;
	}

	if (req->bits.g) {
		memcpy(data->buf_g, si_buf_rd + idx, 6);
	}

	if ((idx > 0) || (req->bits.g)) {
		idx += BMI160_DATA_LEN_GYR;
	}

	if (req->bits.a) {
		memcpy(data->buf_a, si_buf_rd + idx, 6);
	}

	if ((idx > 0) || (req->bits.a)) {
		idx += BMI160_DATA_LEN_ACC;
	}

	if (req->bits.ts) {
		memcpy(data->buf_ts, si_buf_rd + idx, 3);
		data->avail_ts = true;
	}

	//read temperature seperately
	if (req->bits.t) {
		reg_addr_start  = BMI160_REGA_USR_TEMPERATURE_0;
		reg_addr_end    =  BMI160_REGA_USR_TEMPERATURE_1;
		len = reg_addr_end - reg_addr_start + 1;

		status = bmi160_sbus_read_wrapper(port_handle,
				reg_addr_start,
				si_buf_rd,
				len);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		memcpy(data->buf_temp, si_buf_rd + idx, 2);
	}

	return status;
}

#if DEBUG
static void cd2__________________________________________________dummy()
{
}
#endif
sns_dd_bmi160_state_t* sns_dd_bmi160_get_dev(
		sns_ddf_handle_t dd_handle)
{
	bmi160_sub_dev_t *sub_dev = (bmi160_sub_dev_t *)dd_handle;
	return (sns_dd_bmi160_state_t *)sub_dev->private_data;
}

//reviewed
bmi160_sub_dev_t* sns_dd_bmi160_get_subdev_from_type(
		sns_dd_bmi160_state_t *state,
		const sns_ddf_sensor_e       sensor_type)
{
	bmi160_sub_dev_t *sub_dev = NULL;
	uint32_t i;
	uint32_t j;

	for (i = 0; i < state->sub_dev_cnt; i++) {
		sub_dev = state->sub_dev + i;
		for (j = 0; j < BMI160_MAX_SENSORS_NUM; j++) {
			if (sensor_type == sub_dev->sensors[j].sensor_type) {
				return sub_dev;
			}
		}
	}

	return NULL;
}

static inline bmi160_sub_dev_t* sns_dd_bmi160_get_subdev_cache_acc(
		sns_dd_bmi160_state_t *state)
{
	if (!state->sub_dev_cache_acc) {
		state->sub_dev_cache_acc =
			sns_dd_bmi160_get_subdev_from_type(state,
					SNS_DDF_SENSOR_ACCEL);
	}

	return state->sub_dev_cache_acc;
}

static inline bmi160_sub_dev_t* sns_dd_bmi160_get_subdev_cache_gyr(
		sns_dd_bmi160_state_t *state)
{
	if (!state->sub_dev_cache_gyr) {
		state->sub_dev_cache_gyr =
			sns_dd_bmi160_get_subdev_from_type(state,
					SNS_DDF_SENSOR_GYRO);
	}

	return state->sub_dev_cache_gyr;
}

#if BMI160_CONFIG_ENABLE_MAG_IF
static inline bmi160_sub_dev_t* sns_dd_bmi160_get_subdev_cache_mag(
		sns_dd_bmi160_state_t *state)
{
	if (!state->sub_dev_cache_mag) {
		state->sub_dev_cache_mag =
			sns_dd_bmi160_get_subdev_from_type(state,
					SNS_DDF_SENSOR_MAG);
	}

	return state->sub_dev_cache_mag;
}
#endif

//reviewed
bmi160_hw_mod_t* sns_dd_bmi160_get_hw_mod(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type)
{
	uint32_t i;
	uint32_t j;
	struct bmi160_hw_mod *hw_mod;

	for (i = 0; i < BST_ARRAY_SIZE(state->hw_mods); i++) {
		hw_mod = state->hw_mods + i;
		for (j = 0; j < BST_ARRAY_SIZE(hw_mod->sensor_type_supported); j++) {
			if (hw_mod->sensor_type_supported[j] == sensor_type) {
				BMI160_MSG_3(HIGH, "[get_hw_mod] <sensor_type: %d hw_mod: %p hw_mod_type: %d>",
						sensor_type,
						hw_mod,
						hw_mod->hw_mod_type);
				return hw_mod;
			}
		}
	}


	return NULL;
}

inline struct bmi160_hw_mod* sns_dd_bmi160_get_hw_mod_cache_acc(
		sns_dd_bmi160_state_t   *state)
{
	if (!state->hw_mod_cache_acc) {
		state->hw_mod_cache_acc =
			sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_ACCEL);
	}

	return state->hw_mod_cache_acc;
}

inline struct bmi160_hw_mod* sns_dd_bmi160_get_hw_mod_cache_gyr(
		sns_dd_bmi160_state_t   *state)
{
	if (!state->hw_mod_cache_gyr) {
		state->hw_mod_cache_gyr =
			sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_GYRO);
	}

	return state->hw_mod_cache_gyr;
}

#if BMI160_CONFIG_ENABLE_MAG_IF
inline struct bmi160_hw_mod* sns_dd_bmi160_get_hw_mod_cache_mag(
		sns_dd_bmi160_state_t   *state)
{
	if (!state->hw_mod_cache_mag) {
		state->hw_mod_cache_mag =
			sns_dd_bmi160_get_hw_mod(state, SNS_DDF_SENSOR_MAG);
	}

	return state->hw_mod_cache_mag;
}
#endif

//only use this API when you want to keep track of what last_cmd_regv is,
//especially for critical commands such as reset, power mode
sns_ddf_status_e sns_dd_bmi160_send_cmd(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 cmd_regv)
{
	sns_ddf_status_e status;
	uint32_t delay_us;

	status = bmi160_sbus_write_wrapper(state->port_handle,
			BMI160_REGA_CMD_CMD,
			&cmd_regv, 1);

	state->last_cmd_regv = cmd_regv;
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	switch (cmd_regv) {
		case BMI160_REGV_CMD_ACC_MODE_NORMAL:
			//SPEC is 450
			delay_us = BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US + 100;
			break;
		case BMI160_REGV_CMD_GYR_MODE_NORMAL:
			delay_us = BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US + 100;
			break;
		case BMI160_REGV_CMD_MAG_MODE_NORMAL:
			delay_us = BMI160_SPEC_IF_IDLE_TIME_SUSPEND_US + 100;
			break;
		case BMI160_REGV_CMD_SOFT_RESET:
			delay_us = BMI160_SPEC_STARTUP_TIME_MS * 1000;
			break;
		default:
			delay_us = 0;
			break;
	}

	sns_ddf_delay(delay_us);

	status = bmi160_get_reg_hw_err_stat(state->port_handle,
			&state->hw_err_st);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

	if (state->hw_err_st.bits.drop_cmd_err) {
		//status = sns_dd_bmi160_send_cmd(state, state->last_cmd_regv);
	}

	return SNS_DDF_SUCCESS;
}

//reviewed
static void sns_dd_bmi160_format_data_temp(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 buf[],
		sns_ddf_sensor_sample_s samples[1])
{
	int16_t temp_lsb;

	temp_lsb = (int16_t)buf[0] | (((int16_t)buf[1]) << 8);

	samples[0].sample = FX_FLTTOFIX_Q16(temp_lsb * BMI160_SCALE_FACTOR_TEMP + 23);
}

//reviewed
static void sns_dd_bmi160_format_data_acc(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 buf[6],
		sns_ddf_sensor_sample_s samples[3])
{
	struct bmi160_val_acc   val_lsb;
	q16_t                   val_si[3] = {0};


	bmi160_parse_data_acc(buf, 6, &val_lsb);

	val_si[0] = FX_FLTTOFIX_Q16((1 << state->range_idx_acc) * val_lsb.x * BMI160_SCALE_FACTOR_ACC_PM2G);
	val_si[1] = FX_FLTTOFIX_Q16((1 << state->range_idx_acc) * val_lsb.y * BMI160_SCALE_FACTOR_ACC_PM2G);
	val_si[2] = FX_FLTTOFIX_Q16((1 << state->range_idx_acc) * val_lsb.z * BMI160_SCALE_FACTOR_ACC_PM2G);

	sns_ddf_map_axes(&state->axes_map_acc, val_si);

	samples[0].sample = val_si[0] + state->bias_acc[0];
	samples[1].sample = val_si[1] + state->bias_acc[1];
	samples[2].sample = val_si[2] + state->bias_acc[2];

	//TODO: optimize
	samples[0].status = SNS_DDF_SUCCESS;
	samples[1].status = SNS_DDF_SUCCESS;
	samples[2].status = SNS_DDF_SUCCESS;
}

//reviewed
static void sns_dd_bmi160_format_data_gyr(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 buf[6],
		sns_ddf_sensor_sample_s samples[3])
{
	struct bmi160_val_gyr   val_lsb;
	q16_t                   val_si[3] = {0};

	bmi160_parse_data_gyr(buf, 6, &val_lsb);

	val_si[0] = FX_FLTTOFIX_Q16((1 << state->range_idx_gyr) * val_lsb.x * BMI160_SCALE_FACTOR_GYR_PM125DPS);
	val_si[1] = FX_FLTTOFIX_Q16((1 << state->range_idx_gyr) * val_lsb.y * BMI160_SCALE_FACTOR_GYR_PM125DPS);
	val_si[2] = FX_FLTTOFIX_Q16((1 << state->range_idx_gyr) * val_lsb.z * BMI160_SCALE_FACTOR_GYR_PM125DPS);

	sns_ddf_map_axes(&state->axes_map_gyr, val_si);

	samples[0].sample = val_si[0] + state->bias_gyr[0];
	samples[1].sample = val_si[1] + state->bias_gyr[1];
	samples[2].sample = val_si[2] + state->bias_gyr[2];

	samples[0].status = SNS_DDF_SUCCESS;
	samples[1].status = SNS_DDF_SUCCESS;
	samples[2].status = SNS_DDF_SUCCESS;
}

#if BMI160_CONFIG_ENABLE_MAG_IF
static void sns_dd_bmi160_format_data_mag(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 buf[8],
		sns_ddf_sensor_sample_s samples[3])
{
	q16_t                   val_si[3] = {0};

	struct bmi160_slave *slave_mag;
	slave_mag = state->slaves[BMI160_SLAVE_SENSOR_TYPE_MAG];
	slave_mag->parse_data(slave_mag->private_data_slave,
			buf, 8, val_si, 3);

	sns_ddf_map_axes(&state->axes_map_mag, val_si);

	samples[0].sample = val_si[0];
	samples[1].sample = val_si[1];
	samples[2].sample = val_si[2];

	samples[0].status = SNS_DDF_SUCCESS;
	samples[1].status = SNS_DDF_SUCCESS;
	samples[2].status = SNS_DDF_SUCCESS;
}
#endif

static inline
sns_ddf_time_t sns_dd_bmi160_get_ts_backward(
		sns_ddf_time_t now,
		sns_ddf_time_t elapse)
{
	if (now >= elapse) {
		return now - elapse;
	} else {
		return (sns_ddf_time_t)(-1) - (elapse - now) + 1;
	}
}

void sns_dd_bmi160_get_ts_cor(
		enum BMI160_ODR_IDX     odr_idx,
		uint32_t                ts_dev,
		sns_ddf_time_t          ts_sys,
		sns_ddf_time_t          *ts_sys_cor)
{
	uint8_t  lsb_bits = (BMI160_ODR_IDX_1600HZ - BMI160_ODR_IDX_NORMAL_START - odr_idx) + 4;
	uint32_t age_dev = (ts_dev & ((1 << lsb_bits) - 1));
	uint32_t age_sys = BMI160_SSC_US_2_TICKS((uint32_t)(age_dev * BMI160_TS_HW_RES_US_F));

	if (ts_sys >= age_sys) {
		*ts_sys_cor = ts_sys - age_sys;
	} else {
		*ts_sys_cor = ((sns_ddf_time_t)(-1)) - (age_sys - ts_sys) + 1;

		BMI160_MSG_3(HIGH, "WARNING!!! time rewind: <%d %d %d>",
				ts_dev, ts_sys, *ts_sys_cor);
	}
}

//reviewed
static void sns_dd_bmi160_get_couple_ts_host_and_dev(sns_dd_bmi160_state_t *state)
{
	sns_ddf_time_t ts;
	sns_ddf_time_t te;
	uint8_t out;
	uint8_t buf[3] = "";

	ts = sns_ddf_get_timestamp();
	sns_ddf_read_port(state->port_handle,
			BMI160_REGA_USR_SENSORTIME_0,
			buf, 3, &out);
	te = sns_ddf_get_timestamp();


	state->ts_sync_sys_and_dev.ts_sys = ts + sns_dd_bmi160_get_time_elapse_sys(ts, te) / 2;

	bmi160_parse_data_ts(buf, 3, &state->ts_sync_sys_and_dev.ts_dev);
}

/*!
 *  @brief log sensor data
 *
 *  @detail
 *   Logs latest set of sensor data sampled from the sensor
 *
 *  @param[in] state: ptr to the driver structure
 *  @param[in] sample_time: Time that the sensor was sampled
 *
 *
 *  @return
 *
 */
/*=========================================================================*/
//reviewing
void sns_dd_bmi160_log_data_be(
		const sns_ddf_sensor_data_s     *data_collection,
		uint8_t                         num_data_types_per_sample)
{

#if BMI160_CONFIG_ENABLE_LOG_DATA_PKT && !BMI160_CONFIG_RUN_UT
	sns_err_code_e                  err_code;
	sns_log_sensor_data_pkt_s       *log_pkt;
	uint16_t                        num_samples_to_allocate;
	uint16_t                        i;
	log_pkt_t                       log_pkt_type;


	if (!num_data_types_per_sample) {
		return;
	}

	if (data_collection->num_samples / num_data_types_per_sample < 1) {
		return;
	}

	if (data_collection->num_samples / num_data_types_per_sample > 1) {
		num_samples_to_allocate = data_collection->num_samples - 1;
	} else {
		num_samples_to_allocate = 0;
	}

#if BMI160_CONFIG_RUN_ON_OSSC
	log_pkt_type = SNS_LOG_CONVERTED_SENSOR_DATA_PUBLIC;
#else
	log_pkt_type = SNS_LOG_CONVERTED_SENSOR_DATA;
#endif

	//Allocate log packet
	err_code = sns_logpkt_malloc(log_pkt_type,
			sizeof(sns_log_sensor_data_pkt_s)
			+ num_samples_to_allocate * sizeof(log_pkt->samples[0]),
			(void**)&log_pkt);

	if ((SNS_SUCCESS == err_code) && log_pkt) {
		log_pkt->version = SNS_LOG_SENSOR_DATA_PKT_VERSION;
		log_pkt->sensor_id = data_collection->sensor;
		log_pkt->vendor_id = SNS_DDF_VENDOR_BOSCH;

		//Timestamp the log with sample time
		log_pkt->timestamp = data_collection->timestamp;
		log_pkt->end_timestamp = data_collection->end_timestamp;

		//Log the sensor data
		log_pkt->num_data_types = num_data_types_per_sample;
		//CHECK???
		log_pkt->num_samples = data_collection->num_samples / num_data_types_per_sample;

		for (i = 0; i < num_data_types_per_sample; i++) {
			if (i < SNS_LOG_MAX_DATA_TYPES_PER_SENSOR) {
				log_pkt->data[i] = data_collection->samples[i].sample;
			}
		}

		if (num_samples_to_allocate > 0) {
			for (i = 0; i < data_collection->num_samples; i++) {
				log_pkt->samples[i] = data_collection->samples[i].sample;
			}
		}

		//commit log (also frees up the log packet memory)
		err_code = sns_logpkt_commit(log_pkt_type, log_pkt);

		if (SNS_SUCCESS != err_code) {
			DDF_MSG_1(ERROR, "[bmi160_log_data_pkt] - commit error: %d", err_code);
		}
	} else {
		if (SNS_SUCCESS != err_code) {
			DDF_MSG_1(ERROR, "[bmi160_log_data_pkt] - init error: %d", err_code);
		}
	}
#endif
}

void sns_dd_bmi160_log_data(
		const sns_ddf_sensor_data_s     *data_collection,
		uint8_t                         num_data_types_per_sample,
		enum DD_DATA_LOG_CONTEXT        context)
{
	if (0 == num_data_types_per_sample) {
		return;
	}

	sns_dd_bmi160_log_data_be(data_collection, num_data_types_per_sample);

	BST_IGNORE_WARNING_UNUSED_VAR(context);

#if BMI160_CONFIG_ENABLE_LOG_DATA_L1
	BMI160_MSG_4_F(HIGH, "data_log_meta <:0x%x, %d,%d,%d:>",
			(data_collection->sensor << 8) | context,
			data_collection->num_samples,
			data_collection->timestamp,
			data_collection->end_timestamp);
#endif

#if BMI160_CONFIG_ENABLE_LOG_DATA_L2
	uint32_t i;
	sns_ddf_sensor_sample_s  *samples;
	BST_IGNORE_WARNING_UNUSED_VAR(samples);

	if (3 == num_data_types_per_sample) {
		for (i = 0; i < data_collection->num_samples / 3; i++) {
			samples = data_collection->samples + i * 3;
#if BMI160_CONFIG_ENABLE_LOG_DATA_L1
			BMI160_MSG_4_F(HIGH, "data_log_data <:%06d, %d,%d,%d:>",
					i,
					samples[0].sample,
					samples[1].sample,
					samples[2].sample);
#endif
		}

	} else if (1 == num_data_types_per_sample) {
		for (i = 0; i < data_collection->num_samples; i++) {
			samples = data_collection->samples + i;
#if BMI160_CONFIG_ENABLE_LOG_DATA_L1
			BMI160_MSG_3_F(HIGH, "data_log_data <:%06d, %d, %d:>",
					i,
					samples[0].sample,
					0);
#endif
		}
	}
#endif
}

#if BMI160_CONFIG_ENABLE_FIFO
//reviewing
void sns_dd_bmi160_fifo_fill_cache_acc(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 *ff_buf)
{
	sns_ddf_sensor_sample_s  *samples;

	if (3 * state->ff_cache_samples_a.fc
			>= BST_ARRAY_SIZE(state->ff_cache_samples_a.samples)) {
		BMI160_MSG_1(ERROR,
				"[fifo_fill_cache] WARNING!!! the buffer for acc overruns",
				state->ff_cache_samples_a.fc);
		return;
	}

	samples = state->ff_cache_samples_a.samples
		+ 3 * state->ff_cache_samples_a.fc;


	sns_dd_bmi160_format_data_acc(state, ff_buf, samples);

#if BMI160_CONFIG_ENABLE_LOG_DATA_L3
	uint8_t i;
	for (i = 0; i < 6; i++) {
		BMI160_MSG_1(HIGH, "[fill_cache_acc] 0x%02x", ff_buf[i]);
	}

	BMI160_MSG_4(HIGH, "fill_cache_acc <@idx: %d %d %d %d>",
			state->ff_cache_samples_a.fc,
			samples[0].sample,
			samples[1].sample,
			samples[2].sample);

	BMI160_MSG_3(HIGH, "fill_cache_acc <addr %p %p %d>",
			state->ff_cache_samples_a.samples,
			samples,
			(int)sizeof(samples[0]));
#endif

	state->ff_cache_samples_a.fc += 1;
}

//reviewing
void sns_dd_bmi160_fifo_fill_cache_gyr(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 *ff_buf)
{
	sns_ddf_sensor_sample_s  *samples;


	if (3 * state->ff_cache_samples_g.fc
			>= BST_ARRAY_SIZE(state->ff_cache_samples_g.samples)) {
		BMI160_MSG_1(ERROR,
				"[fifo_fill_cache] WARNING!!! the buffer for gyr overruns",
				state->ff_cache_samples_g.fc);
		return;
	}

	samples = state->ff_cache_samples_g.samples
		+ 3 * state->ff_cache_samples_g.fc;


	sns_dd_bmi160_format_data_gyr(state, ff_buf, samples);
#if BMI160_CONFIG_ENABLE_LOG_DATA_L3
	BMI160_MSG_3(HIGH, "fill_cache_gyr <%d %d %d>",
			samples[0].sample,
			samples[1].sample,
			samples[2].sample);
#endif

	state->ff_cache_samples_g.fc += 1;
}

//reviewing
void sns_dd_bmi160_fifo_fill_cache_mag(
		sns_dd_bmi160_state_t   *state,
		uint8_t                 *ff_buf)
{
#if BMI160_CONFIG_ENABLE_MAG_IF
	sns_ddf_sensor_sample_s  *samples;


	if (state->ff_cache_samples_m.fc
			>= BST_ARRAY_SIZE(state->ff_cache_samples_m.samples)) {
		BMI160_MSG_1(ERROR,
				"[fifo_fill_cache] WARNING!!! the buffer for mag overruns",
				state->ff_cache_samples_g.fc);
		return;
	}

	samples = state->ff_cache_samples_m.samples
		+ 3 * state->ff_cache_samples_m.fc;

	state->ff_cache_samples_m.fc += 1;

	sns_dd_bmi160_format_data_mag(state, ff_buf, samples);
#endif
}

//reviewing

//reviewing
static void sns_dd_bmi160_fifo_update_sync_info(
		sns_dd_bmi160_state_t           *state,
		bmi160_fifo_parse_result_t      *ff_parse_rslt)
{
	if (ff_parse_rslt->bits.ff_avail_acc
			|| ff_parse_rslt->bits.ff_avail_gyr
			|| ff_parse_rslt->bits.ff_avail_mag) {
		state->ff_sample_sync_info.fc_master += 1;
	}


	if (ff_parse_rslt->bits.ff_avail_acc) {
		state->ff_sample_sync_info.last_sync_marker_a.fc = state->ff_cache_samples_a.fc;
		state->ff_sample_sync_info.last_sync_marker_a.fc_master = state->ff_sample_sync_info.fc_master;
	}

	if (ff_parse_rslt->bits.ff_avail_gyr) {
		state->ff_sample_sync_info.last_sync_marker_g.fc = state->ff_cache_samples_g.fc;
		state->ff_sample_sync_info.last_sync_marker_g.fc_master = state->ff_sample_sync_info.fc_master;
	}

#if BMI160_CONFIG_ENABLE_MAG_IF
	if (ff_parse_rslt->bits.ff_avail_mag) {
		state->ff_sample_sync_info.last_sync_marker_m.fc = state->ff_cache_samples_m.fc;
		state->ff_sample_sync_info.last_sync_marker_m.fc_master = state->ff_sample_sync_info.fc_master;
	}
#endif
}

static sns_ddf_status_e sns_dd_bmi160_fifo_parse_frames(
		sns_dd_bmi160_state_t           *state,
		uint8_t                         *ff_buf,
		uint32_t                        ff_buf_len,
		uint32_t                        *ff_proc_len_left,
		bmi160_fifo_parse_result_t      *ff_parse_rslt)
{
	uint16_t                err_code = 0;

	uint8_t                 frame_header;
	uint8_t                 fh_mode;
	uint8_t                 fh_param;

	uint8_t                 frames_skipped;
	uint8_t                 frame_input_cfg;
	uint8_t                 frame_length;

	uint32_t                ff_buf_idx = 0;

#if BMI160_CONFIG_ENABLE_LOG_DATA_L3
	uint16_t i;

	for (i = 0; i < ff_buf_len; i++) {
		BMI160_MSG_2(HIGH, "[parse_fifob] @%03d: 0x%02x",
				i, ff_buf[i]);

		if (0x80 == ff_buf[i]) {
			i++;
			BMI160_MSG_2(HIGH, "[parse_fifob] %d bytes omitted next byte: 0x%02x",
					ff_buf_len - i, ff_buf[i]);
			break;
		}
	}
#endif

	err_code = 0;
	ff_buf_idx = 0;

	while ((ff_buf_idx < ff_buf_len) &&  (!err_code)) {
		frame_header = ff_buf[ff_buf_idx];
		ff_buf_idx += 1;
		if (BMI160_FF_FH_EMPTY == frame_header) {
			// fifo empty
			BMI160_MSG_1(ERROR, "[parse_fifo]@%d frame_end",
					ff_buf_idx - 1);
			ff_parse_rslt->bits.ff_avail_end_frame = 1;
			break;
		}

		fh_mode         = BMI160_FF_FH_MODE(frame_header);
		fh_param        = BMI160_FF_FH_PARAM(frame_header);

#if BMI160_CONFIG_ENABLE_LOG_DATA_L3
		BMI160_MSG_3(HIGH, "[parse_fifo] frame_header = 0x%02x fh_mode: 0x%02x fh_param: 0x%02x",
				frame_header, fh_mode, fh_param);
#endif

		if (BMI160_FF_FH_MODE_REGULAR == fh_mode) {
			frame_length = 0;
			frame_length += ((fh_param & B2_SET) ? BMI160_FF_DATA_LEN_MAG : 0);
			frame_length += ((fh_param & B1_SET) ? BMI160_FF_DATA_LEN_GYR : 0);
			frame_length += ((fh_param & B0_SET) ? BMI160_FF_DATA_LEN_ACC : 0);

			if (ff_buf_idx + frame_length > ff_buf_len) {
				// buf is over
				BMI160_MSG_2(ERROR,
						"[parse_fifo] NOTICE!!! partial read of frame %d bytes yet to be read, total: %d",
						ff_buf_idx + frame_length - ff_buf_len, ff_buf_len);

				err_code = (BMI160_FF_FRAME_ERR_PARTIAL_READ << 8) | frame_header;
				break;
			}

			if (fh_param & B2_SET) {
				// mag data
				sns_dd_bmi160_fifo_fill_cache_mag(state, ff_buf + ff_buf_idx);
#if BMI160_CONFIG_ENABLE_MAG_IF
				if (state->ff_cache_samples_m.fc >= BMI160_FF_CACHE_SIZE_ACC) {
					ff_parse_rslt->bits.ff_cache_full_mag = 1;
				}
#endif

				ff_buf_idx += BMI160_FF_DATA_LEN_MAG;
				ff_parse_rslt->bits.ff_avail_mag = 1;
			}

			if (fh_param & B1_SET) {
				// gyr data
				sns_dd_bmi160_fifo_fill_cache_gyr(state, ff_buf + ff_buf_idx);
				if (state->ff_cache_samples_g.fc >= BMI160_FF_CACHE_SIZE_ACC) {
					ff_parse_rslt->bits.ff_cache_full_gyr = 1;
				}

				ff_buf_idx += BMI160_FF_DATA_LEN_GYR;
				ff_parse_rslt->bits.ff_avail_gyr = 1;
			}

			if (fh_param & B0_SET) {
				// acc data
				sns_dd_bmi160_fifo_fill_cache_acc(state, ff_buf + ff_buf_idx);
				if (state->ff_cache_samples_a.fc >= BMI160_FF_CACHE_SIZE_ACC) {
					ff_parse_rslt->bits.ff_cache_full_acc = 1;
				}

				ff_buf_idx += BMI160_FF_DATA_LEN_ACC;
				ff_parse_rslt->bits.ff_avail_acc = 1;
			}

			sns_dd_bmi160_fifo_update_sync_info(state, ff_parse_rslt);

			if (unlikely(ff_parse_rslt->bits.ff_cache_full_mag ||
						ff_parse_rslt->bits.ff_cache_full_gyr ||
						ff_parse_rslt->bits.ff_cache_full_acc)) {
				*ff_proc_len_left = ff_buf_len - ff_buf_idx;
				goto exit_parse_ff_frames;
			}

		} else if (BMI160_FF_FH_MODE_CTRL == fh_mode) {
			switch (fh_param) {
				case 0x00:
					if (ff_buf_idx + 1 > ff_buf_len) {
						err_code = (BMI160_FF_FRAME_ERR_PARTIAL_READ << 8)
							| frame_header;
						break;
					}
					//fifo overflowed
					ff_parse_rslt->bits.ff_overflow = true;

					frames_skipped = ff_buf[ff_buf_idx];
					ff_buf_idx += 1;
					BMI160_MSG_2(ERROR, "[parse_fifo]@%d frame_ctrl WARNING!!! frames_skipped = 0x%02x",
							ff_buf_idx - 2,
							frames_skipped);

					BST_IGNORE_WARNING_UNUSED_VAR(frames_skipped);
					break;
				case 0x01:
					if (ff_buf_idx + 3 > ff_buf_len) {
						err_code = (BMI160_FF_FRAME_ERR_PARTIAL_READ << 8)
							| frame_header;
						break;
					}
					bmi160_parse_data_ts(ff_buf + ff_buf_idx, 3,
							&state->ts_ff_dev_last_frame);
					BMI160_MSG_4(HIGH,
							"[parse_fifo]@%d frame_ctrl sensortime raw (hex): <%02x %02x %02x>",
							ff_buf_idx - 1,
							ff_buf[ff_buf_idx],
							ff_buf[ff_buf_idx + 1],
							ff_buf[ff_buf_idx + 2]);
					BMI160_MSG_1(HIGH,
							"sensortime = %d",
							state->ts_ff_dev_last_frame);

					ff_buf_idx += 3;
					ff_parse_rslt->bits.ff_avail_ts = 1;
					break;
				case 0x02:
					// Fifo_Input_Config Frame
					if (ff_buf_idx + 1 > ff_buf_len) {
						err_code = (BMI160_FF_FRAME_ERR_PARTIAL_READ << 8)
							| frame_header;
						break;
					}

					frame_input_cfg = ff_buf[ff_buf_idx];
					ff_buf_idx += 1;
					BMI160_MSG_2(ERROR, "[parse_fifo]@%d frame_ctrl Fifo_Input_Config = 0x%02x",
							ff_buf_idx - 2,
							frame_input_cfg);
					BST_IGNORE_WARNING_UNUSED_VAR(frame_input_cfg);
					break;
				default:
					BMI160_MSG_2(ERROR,
							"[parse_fifo]%@d frame_unknown WARNING!!! frame format unknown frame_header: 0x%02x",
							ff_buf_idx,
							frame_header);
					err_code = (BMI160_FF_FRAME_ERR_UNKNOWN << 8)
						| frame_header;
					break;
			}
		} else {
			BMI160_MSG_2(ERROR, "[parse_fifo]@%d frame_unknown WARNING!!! unknown fifo frame_header: 0x%02x",
					ff_buf_idx - 1,
					frame_header);
			err_code = (BMI160_FF_FRAME_ERR_UNKNOWN << 8)
				| frame_header;
			break;
		}
	}
	//end of while

	*ff_proc_len_left = 0;
exit_parse_ff_frames:
	if (err_code &&
			(((err_code >> 8) & 0xff) != BMI160_FF_FRAME_ERR_PARTIAL_READ)) {
		BMI160_MSG_3(ERROR, "[parse_fifo] WARNING!!! error seen during parsing: <err: 0x%04x %d %d>",
				err_code, ff_buf_idx, ff_buf_len);
	}

	return SNS_DDF_SUCCESS;
}

static void sns_dd_bmi160_fifo_populate_sample_ts(
		sns_dd_bmi160_state_t   *state,
		sns_ddf_sensor_e        sensor_type,
		uint16_t                fc)
{
	bmi160_fifo_sample_sync_info_t          *ff_sample_sync_info;
	sns_ddf_sensor_data_s                   *ff_cache;
	struct bmi160_fifo_sync_marker          *sync_marker;
	uint32_t                                fc_master_1st_frame;
	uint32_t                                fc_master_last_frame;
	bmi160_hw_mod_t                         *hw_mod;
	sns_ddf_time_t                          end_timestamp_last_cache;
	uint8_t                                 avail_last_ts;
	sns_ddf_time_t                          ts_curr;
	sns_ddf_time_t                          end_timestamp;
	int8_t                                  odr_times;


	ff_sample_sync_info = &state->ff_sample_sync_info;

	switch (sensor_type) {
		case SNS_DDF_SENSOR_ACCEL:
			ff_cache = &state->ff_cache_a;
			sync_marker = &ff_sample_sync_info->last_sync_marker_a;
			hw_mod = sns_dd_bmi160_get_hw_mod_cache_acc(state);
			break;
		case SNS_DDF_SENSOR_GYRO:
			ff_cache = &state->ff_cache_g;
			sync_marker = &ff_sample_sync_info->last_sync_marker_g;
			hw_mod = sns_dd_bmi160_get_hw_mod_cache_gyr(state);
			break;
#if BMI160_CONFIG_ENABLE_MAG_IF
		case SNS_DDF_SENSOR_MAG:
			ff_cache = &state->ff_cache_m;
			sync_marker = &ff_sample_sync_info->last_sync_marker_m;
			hw_mod = sns_dd_bmi160_get_hw_mod_cache_mag(state);
			break;
#endif
		default:
			return;
	}

	if ((NULL == hw_mod) || (NULL == state->hw_mod_ff_master)) {
		BMI160_MSG_2(HIGH, "WARNING!!! NULL pointer <%p %p>",
				hw_mod, state->hw_mod_ff_master);
		return;
	}

	odr_times = state->hw_mod_ff_master->odr_curr / hw_mod->odr_curr;

	//fc_master_1st_frame and fc_master_last_frame must be unsigned
	fc_master_1st_frame = sync_marker->fc_master -
		(sync_marker->fc - 1) * odr_times;
	fc_master_last_frame = sync_marker->fc_master +
		((int32_t)fc - (int32_t)sync_marker->fc) * odr_times;

	if (state->hw_mod_ff_master->odr_curr < hw_mod->odr_curr) {
		BMI160_MSG_3(HIGH,
				"[populate_sample_ts] WARNING!!! hw_mod_ff_master not updated properly<%d %d %d>",
				sensor_type,
				state->hw_mod_ff_master->hw_mod_type,
				hw_mod->odr_curr);
	}

	end_timestamp_last_cache = ff_cache->end_timestamp;

	avail_last_ts = ff_sample_sync_info->avail_last_ts;
	//CHECK: overflow
	if (BST_GET_VAL_BIT(avail_last_ts, hw_mod->hw_mod_type)) {
		ff_cache->timestamp = end_timestamp_last_cache +
			odr_times * ff_sample_sync_info->ts_itvl_master_sample_est;
	} else {
		ff_sample_sync_info->avail_last_ts =
			BST_SET_VAL_BIT(avail_last_ts, hw_mod->hw_mod_type);


		ff_cache->timestamp = ff_sample_sync_info->ts_sys_last_sync_ref
			+ ((int32_t)fc_master_1st_frame - (int32_t)ff_sample_sync_info->fc_master_last_sync_ref)
			* ff_sample_sync_info->ts_itvl_master_sample_est;

		ts_curr = sns_ddf_get_timestamp();

		if (ts_curr >= end_timestamp_last_cache) {
			if (ff_cache->timestamp <= end_timestamp_last_cache) {
				ff_cache->timestamp = end_timestamp_last_cache + BMI160_SSC_US_2_TICKS(39);

				BMI160_MSG_2(HIGH, "WARNING!!! time offset t.s LT l.e <%d %d>",
						ff_cache->timestamp,
						end_timestamp_last_cache);
			}
		} else {
			BMI160_MSG_2(HIGH, "NOTICE!!! time rewind <%d %d>",
					end_timestamp_last_cache,
					ts_curr);
		}
	}

	//CHECK: overflow
	if (fc >= 1) {
		end_timestamp = ff_sample_sync_info->ts_sys_last_sync_ref
			+ ((int32_t)fc_master_last_frame - (int32_t)ff_sample_sync_info->fc_master_last_sync_ref)
			* ff_sample_sync_info->ts_itvl_master_sample_est;

		if (end_timestamp <= ff_cache->timestamp) {
#if BMI160_CONFIG_ENABLE_DBG_MSG
			sns_ddf_time_t end_timestamp_est;
			end_timestamp_est = end_timestamp;
#endif //BMI160_CONFIG_ENABLE_DBG_MSG

			end_timestamp = ff_cache->timestamp +
				((int32_t)fc_master_last_frame - (int32_t)fc_master_1st_frame) *
				ff_sample_sync_info->ts_itvl_master_sample_est;
#if BMI160_CONFIG_ENABLE_DBG_MSG
			BMI160_MSG_3(HIGH, "NOTICE!!! time offset t.s GT t.e <%d %d cor: %d>",
					ff_cache->timestamp,
					end_timestamp_est,
					end_timestamp);
#endif //BMI160_CONFIG_ENABLE_DBG_MSG 
		}

		if (fc > 1) {
			ff_cache->end_timestamp = end_timestamp;
		} else {
			ff_cache->end_timestamp = (end_timestamp + ff_cache->timestamp) / 2;
			ff_cache->timestamp = ff_cache->end_timestamp;
		}
	}

#if BMI160_CONFIG_ENABLE_LOG_DATA_L2
	BMI160_MSG_4(HIGH, "[populate_sample_ts] <sensor_type: %d mark fc: %d marker fc_m: %d avail: %d>",
			sensor_type,
			sync_marker->fc,
			sync_marker->fc_master,
			avail_last_ts);

	BMI160_MSG_3(HIGH, "[populate_sample_ts] <master_last_sync_ref fc: %d ts_sys: %d est_itvl: %d>",
			ff_sample_sync_info->fc_master_last_sync_ref,
			ff_sample_sync_info->ts_sys_last_sync_ref,
			ff_sample_sync_info->ts_itvl_master_sample_est);
#endif
}

static sns_ddf_status_e sns_dd_bmi160_fifo_post_process(
		sns_dd_bmi160_state_t           *state,
		uint8_t                         in_irq,
		uint8_t                         trigger_now)
{
	uint16_t        idx;
	uint32_t        size;
	uint16_t        frame_cnt_acc;
	uint16_t        frame_cnt_gyr;
	sns_ddf_sensor_sample_s           *buf;

#if BMI160_CONFIG_ENABLE_MAG_IF
	uint16_t        frame_cnt_mag = 0;
	frame_cnt_mag = state->ff_cache_samples_m.fc;
#endif

	frame_cnt_acc = state->ff_cache_samples_a.fc;
	frame_cnt_gyr = state->ff_cache_samples_g.fc;

	if (in_irq || !trigger_now) {
		if (frame_cnt_acc >= state->ff_wml_req_acc) {
			buf = state->ff_cache_samples_a.samples;
			idx = state->ff_wml_req_acc * 3;
			size = (frame_cnt_acc - state->ff_wml_req_acc)
				* 3 * sizeof(sns_ddf_sensor_sample_s);

			if (size > 0) {
				memcpy(buf, buf + idx, size);
			}

			state->ff_cache_samples_a.fc -= state->ff_wml_req_acc;
		}

		if (frame_cnt_gyr >= state->ff_wml_req_gyr) {
			buf = state->ff_cache_samples_g.samples;
			idx = state->ff_wml_req_gyr * 3;
			size = (frame_cnt_gyr - state->ff_wml_req_gyr)
				* 3 * sizeof(sns_ddf_sensor_sample_s);
			if (size > 0) {
				memcpy(buf, buf + idx, size);
			}

			state->ff_cache_samples_g.fc -= state->ff_wml_req_gyr;
		}
#if BMI160_CONFIG_ENABLE_MAG_IF
		if (frame_cnt_mag >= state->ff_wml_req_mag) {
			buf = state->ff_cache_samples_m.samples;
			idx = state->ff_wml_req_mag * 3;
			size = (frame_cnt_mag - state->ff_wml_req_mag)
				* 3 * sizeof(sns_ddf_sensor_sample_s);
			if (size > 0) {
				memcpy(buf, buf + idx, size);
			}

			state->ff_cache_samples_m.fc -= state->ff_wml_req_mag;
		}
#endif
	} else {
		state->ff_cache_samples_a.fc = 0;
		state->ff_cache_samples_g.fc = 0;
#if BMI160_CONFIG_ENABLE_MAG_IF
		state->ff_cache_samples_m.fc = 0;
#endif
	}

	return SNS_DDF_SUCCESS;
}

static void sns_dd_bmi160_fifo_estimate_itvl_master(
		sns_dd_bmi160_state_t   *state,
		uint32_t                fc_master_change,
		bmi160_time_info_t      *time_info)
{
	sns_ddf_time_t                  ts_itvl_master_sample_est = 0;
	sns_ddf_time_t                  ts_cor;
	uint32_t                        ts_dev_update_msb;

	struct ts_pair_sys_and_dev ts_sync_sys_and_dev_last = state->ts_sync_sys_and_dev;
	uint8_t lsb_bits = (BMI160_ODR_IDX_1600HZ - BMI160_ODR_IDX_NORMAL_START - state->hw_mod_ff_master->odr_map_idx) + 4;


	BST_IGNORE_WARNING_UNUSED_VAR(fc_master_change);

	sns_dd_bmi160_get_couple_ts_host_and_dev(state);

	if (state->ff_sample_sync_info.avail_master_itvl_est) {
		ts_itvl_master_sample_est = sns_dd_bmi160_get_time_elapse_sys(
				ts_sync_sys_and_dev_last.ts_sys,
				state->ts_sync_sys_and_dev.ts_sys) * (1 << lsb_bits) * 1.0 /
			bmi160_get_time_elapse_dev_lsb(ts_sync_sys_and_dev_last.ts_dev,
					state->ts_sync_sys_and_dev.ts_dev);

		if (BST_TIME_ELAPSE_NEAR_ITVL(ts_itvl_master_sample_est,
					state->ff_sample_sync_info.ts_itvl_master_sample_exp)) {
			state->ff_sample_sync_info.ts_itvl_master_sample_est =
				(state->ff_sample_sync_info.ts_itvl_master_sample_est * BMI160_CONFIG_TS_ITVL_EST_COEF
				+ ts_itvl_master_sample_est * (10 - BMI160_CONFIG_TS_ITVL_EST_COEF)) / 10;
		}


#if BMI160_CONFIG_ENABLE_LOG_DATA_L2
		BMI160_MSG_4(HIGH, "[estimate_itvl_master] <s1: %d d1: 0x%x s2: %d d2: 0x%x>",
				ts_sync_sys_and_dev_last.ts_sys,
				ts_sync_sys_and_dev_last.ts_dev,
				state->ts_sync_sys_and_dev.ts_sys,
				state->ts_sync_sys_and_dev.ts_dev);
#endif
	} else {
		state->ff_sample_sync_info.avail_master_itvl_est = 1;
	}

	ts_dev_update_msb = bmi160_get_ts_dev_update_msb(
			time_info->ts_dev_ff,
			state->ts_sync_sys_and_dev.ts_dev,
			lsb_bits);

	sns_dd_bmi160_get_ts_cor(
			state->hw_mod_ff_master->odr_map_idx,
			state->ts_sync_sys_and_dev.ts_dev,
			state->ts_sync_sys_and_dev.ts_sys,
			&ts_cor);

	if (ts_dev_update_msb > 0) {
		ts_cor = sns_dd_bmi160_get_ts_backward(
				ts_cor,
				ts_dev_update_msb *
				state->ff_sample_sync_info.ts_itvl_master_sample_est);
	}

	state->ff_sample_sync_info.ts_sys_last_sync_ref         = ts_cor;
	state->ff_sample_sync_info.fc_master_last_sync_ref      = state->ff_sample_sync_info.fc_master;


	BMI160_MSG_4(HIGH, "[estimate_itvl_master] <lsb_bits: %d msb: %d est_itvl: %d sys_ref: %d>",
			lsb_bits, ts_dev_update_msb, ts_itvl_master_sample_est, ts_cor);
}

static sns_ddf_status_e sns_dd_bmi160_fifo_process_samples_ts(
		sns_dd_bmi160_state_t           *state,
		uint8_t                         in_irq,
		uint8_t                         trigger_now,
		bmi160_fifo_status_t            *ff_status,
		bmi160_time_info_t              *time_info)
{
	//TODO: when fifo overflowed, we shall not continue?
	uint16_t        frame_cnt_acc;
	uint16_t        frame_cnt_gyr;


	frame_cnt_acc = state->ff_cache_samples_a.fc;
	frame_cnt_gyr = state->ff_cache_samples_g.fc;

#if BMI160_CONFIG_ENABLE_MAG_IF
	uint16_t        frame_cnt_mag = 0;
	frame_cnt_mag = state->ff_cache_samples_m.fc;

#endif
	if ((in_irq) || (!trigger_now)) {
		if ((frame_cnt_acc >= state->ff_wml_req_acc)
				&& (state->ff_wml_req_acc > 0)) {
			state->ff_cache_a.num_samples = state->ff_wml_req_acc * 3;
			frame_cnt_acc = state->ff_wml_req_acc;
			ff_status->ff_rdy_acc = true;
		}

		if ((frame_cnt_gyr >= state->ff_wml_req_gyr)
				&& (state->ff_wml_req_gyr > 0)) {
			frame_cnt_gyr = state->ff_wml_req_gyr;
			state->ff_cache_g.num_samples = state->ff_wml_req_gyr * 3;
			ff_status->ff_rdy_gyr = true;
		}

#if BMI160_CONFIG_ENABLE_MAG_IF
		if ((frame_cnt_mag >= state->ff_wml_req_mag)
				&& (state->ff_wml_req_mag > 0)) {
			frame_cnt_mag = state->ff_wml_req_mag;
			state->ff_cache_m.num_samples = state->ff_wml_req_mag * 3;
			ff_status->ff_rdy_mag = true;
		}
#endif
	} else {
		//called from trigger_fifo_data()
		if (frame_cnt_acc > 0) {
			state->ff_cache_a.num_samples = frame_cnt_acc * 3;
			ff_status->ff_rdy_acc = true;
		}

		if (frame_cnt_gyr > 0) {
			state->ff_cache_g.num_samples = frame_cnt_gyr * 3;
			ff_status->ff_rdy_gyr = true;
		}

#if BMI160_CONFIG_ENABLE_MAG_IF
		if (frame_cnt_mag > 0) {
			state->ff_cache_m.num_samples = frame_cnt_mag * 3;
			ff_status->ff_rdy_mag = true;
		}
#endif
	}

	if (ff_status->ff_rdy_acc) {
		sns_dd_bmi160_fifo_populate_sample_ts(state, SNS_DDF_SENSOR_ACCEL, frame_cnt_acc);
	}

	if (ff_status->ff_rdy_gyr) {
		sns_dd_bmi160_fifo_populate_sample_ts(state, SNS_DDF_SENSOR_GYRO, frame_cnt_gyr);
	}

#if BMI160_CONFIG_ENABLE_MAG_IF
	if (ff_status->ff_rdy_mag) {
		sns_dd_bmi160_fifo_populate_sample_ts(state, SNS_DDF_SENSOR_MAG, frame_cnt_mag);
	}
#endif

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_bmi160_fifo_read_out_frames(
		sns_dd_bmi160_state_t           *state,
		uint16_t                        ff_count,
		uint8_t                         in_irq,
		uint8_t                         trigger_now,
		struct bmi160_fifo_status       *ff_status)
{
#if BMI160_CONFIG_ENABLE_FIFO
	sns_ddf_status_e        status;
	uint8_t         *ff_buf = state->ff_cache_raw;

	uint32_t        ff_bytes_to_read = 0;
	uint32_t        ff_bytes_read = 0;
	uint32_t        ff_buf_proc_left = 0;

	uint32_t        fc_master_old = 0;
	int16_t         i;

	bmi160_fifo_parse_result_t ff_parse_rslt = {.rslt = 0};
	bmi160_time_info_t time_info = {0};

	ff_bytes_to_read = ff_count + (BMI160_FF_FRAME_LEN_TS + 4);

	if (ff_bytes_to_read > BMI160_SSC_I2C_RD_LEN_MAX) {
		ff_bytes_to_read = BMI160_SSC_I2C_RD_LEN_MAX;
	}

	if (in_irq) {
		time_info.ts_sys_irq = state->ts_ff_irq;
		time_info.ts_dev_reg = state->reg_int_ctx.ts_hw;
	}

	fc_master_old = state->ff_sample_sync_info.fc_master;

	i = 0;
	do {
		status = bmi160_read_fifo_bytes(state->port_handle,
				ff_buf, ff_bytes_to_read, &ff_bytes_read);

		BMI160_MSG_3(HIGH, "[read_out_fifo] ff_count: %d ff_bytes_to_read: %d @round: %d",
				ff_count, ff_bytes_read, i);

		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		ff_buf_proc_left = 0;
		ff_parse_rslt.rslt = 0;
		status = sns_dd_bmi160_fifo_parse_frames(state, ff_buf, ff_bytes_read, &ff_buf_proc_left, &ff_parse_rslt);
		if (unlikely(ff_buf_proc_left > 0)) {
			BMI160_MSG_1(HIGH, "[read_out_fifo] NOTICE!!! ff_buf_proc_left: %d not handled", ff_buf_proc_left);
			//LKTD
		}
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		if (ff_parse_rslt.bits.ff_avail_ts) {
			time_info.ts_dev_ff = state->ts_ff_dev_last_frame;

			if (fc_master_old != state->ff_sample_sync_info.fc_master) {
				sns_dd_bmi160_fifo_estimate_itvl_master(
						state,
						BST_ABS_DIST(fc_master_old, state->ff_sample_sync_info.fc_master),
						&time_info);
			} else {
				BMI160_MSG_1(HIGH,
						"[read_out_fifo] WARNING!!! odds @round: %d get sensortime but no new frames",
						i);
			}
		} else {
			if (fc_master_old != state->ff_sample_sync_info.fc_master) {
				if (ff_parse_rslt.bits.ff_avail_end_frame) {
					BMI160_MSG_0(HIGH,
							"[read_out_fifo] NOTICE!!! get EMPTY but not sensortime");
					break;
				}

				if (i > 5) {
					BMI160_MSG_0(HIGH, "[read_out_fifo] NOTICE!!! did not get sensortime from fifo, give up");
					break;
				}

				i++;
				BMI160_MSG_1(HIGH,
						"[read_out_fifo] NOTICE!!! did not get sensortime from fifo, retry @round: %d",
						i);

				ff_bytes_to_read = (BMI160_FF_DATA_LEN_MAG + BMI160_FF_DATA_LEN_GYR + BMI160_FF_DATA_LEN_ACC) * i
					+ (BMI160_FF_FRAME_LEN_TS + 4);

				if (ff_bytes_to_read > BMI160_SSC_I2C_RD_LEN_MAX) {
					ff_bytes_to_read = BMI160_SSC_I2C_RD_LEN_MAX;
				}

				continue;
			} else {
				BMI160_MSG_2(HIGH,
						"[read_out_fifo] NOTICE!!! did not get any new frame @round: %d in_irq: %d",
						i, in_irq);
				break;
			}
		}

		if (ff_parse_rslt.bits.ff_avail_ts) {
			break;
		}
	} while (1);

	if (fc_master_old != state->ff_sample_sync_info.fc_master) {
		status = sns_dd_bmi160_fifo_process_samples_ts(state,
				in_irq,
				trigger_now,
				ff_status,
				&time_info);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	} else {
		BMI160_MSG_0(HIGH, "NOTICE!!! nothing to process this time");
	}
#endif
	return SNS_DDF_SUCCESS;
}
#endif


sns_ddf_status_e sns_dd_bmi160_fifo_flush(
		sns_dd_bmi160_state_t           *state,
		uint16_t                        num_samples,
		uint32_t                        caller)
{
	sns_ddf_status_e status =  SNS_DDF_SUCCESS;
#if BMI160_CONFIG_ENABLE_FIFO
	bmi160_sub_dev_t *sub_dev_acc = sns_dd_bmi160_get_subdev_cache_acc(state);
	if (sub_dev_acc == NULL) {
	   return SNS_DDF_EINVALID_PARAM;
	}
	bmi160_sub_dev_t *sub_dev_gyr = sns_dd_bmi160_get_subdev_cache_gyr(state);
	if (sub_dev_gyr == NULL) {
	   return SNS_DDF_EINVALID_PARAM;
	}
#if BMI160_CONFIG_ENABLE_MAG_IF
	bmi160_sub_dev_t *sub_dev_mag = sns_dd_bmi160_get_subdev_cache_mag(state);
	if (sub_dev_mag == NULL) {
	   return SNS_DDF_EINVALID_PARAM;
	}
#endif
	struct bmi160_fifo_status ff_status = {0};
	uint16_t ff_count = 0;

	if (0 == num_samples) {
		if (!BMI160_CHIP_REV_IS_A2(state->chip_rev)) {
			status = bmi160_get_reg_fifo_count(state->port_handle, &ff_count);
			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		} else {
			ff_count = state->ff_suggested_bytes2read;
		}
	} else {
		ff_count = num_samples;
	}

	BMI160_MSG_3_F(ERROR,
			"[bmi160_fifo_flush] num_samples: %d caller: %d ff_count: %d",
			num_samples, caller, ff_count);

	if (ff_count > 0) {
		status = sns_dd_bmi160_fifo_read_out_frames(state, ff_count, false, true, &ff_status);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);

		if (ff_status.ff_rdy_acc) {
			status |= sns_ddf_smgr_notify_data(sub_dev_acc->smgr_handle,
					&state->ff_cache_a, 1);

			sns_dd_bmi160_log_data(&state->ff_cache_a, 3, DD_DATA_LOG_CONTEXT_FIFO_FLUSH);
		}

		if (ff_status.ff_rdy_gyr) {
			status |= sns_ddf_smgr_notify_data(sub_dev_gyr->smgr_handle,
					&state->ff_cache_g, 1);
			sns_dd_bmi160_log_data(&state->ff_cache_g, 3, DD_DATA_LOG_CONTEXT_FIFO_FLUSH);
		}

#if BMI160_CONFIG_ENABLE_MAG_IF
		if (ff_status.ff_rdy_mag) {
			status |= sns_ddf_smgr_notify_data(sub_dev_mag->smgr_handle,
					&state->ff_cache_m, 1);

			sns_dd_bmi160_log_data(&state->ff_cache_m, 3, DD_DATA_LOG_CONTEXT_FIFO_FLUSH);
		}
#endif
		sns_dd_bmi160_fifo_post_process(state, false, true);

		//sns_dd_bmi160_send_cmd(state, BMI160_REGV_CMD_FIFO_FLUSH);
	}

#endif
	return status;
}

#if BMI160_CONFIG_ENABLE_INT_DOUBLE_TAP
//reviewed
static sns_ddf_tap_dir_e sns_dd_bmi160_get_tap_dir(uint8_t int_stat)
{
	sns_ddf_tap_dir_e ret;
	uint8_t dir_first_tap;
	uint8_t sign;
	sign = BST_GET_VAL_BITBLOCK(int_stat, 7, 7);
	dir_first_tap = bmi160_get_tap_first(int_stat);
	switch (dir_first_tap) {
		case BMI160_INT_INFO_TAP_FIRST_X:
			if (sign)
				ret = SNS_DDF_TAP_DIR_NEG_X;
			else
				ret = SNS_DDF_TAP_DIR_POS_X;
			break;
		case BMI160_INT_INFO_TAP_FIRST_Y:
			if (sign)
				ret = SNS_DDF_TAP_DIR_NEG_Y;
			else
				ret = SNS_DDF_TAP_DIR_POS_Y;
			break;
		case BMI160_INT_INFO_TAP_FIRST_Z:
			if (sign)
				ret = SNS_DDF_TAP_DIR_NEG_Z;
			else
				ret = SNS_DDF_TAP_DIR_POS_Z;
			break;
		default:
			ret = SNS_DDF_TAP_DIR_NONE;
	}
	return ret;
}

static sns_ddf_status_e sns_dd_bmi160_handle_irq_dt(
		sns_dd_bmi160_state_t           *state,
		sns_ddf_time_t                  ts_irq)
{
	sns_ddf_status_e        status;
	bmi160_sub_dev_t        *sub_dev;
	sns_ddf_time_t          timestamp = ts_irq;
	q16_t                   sample_dt;
	sns_ddf_sensor_data_s   *data_dt;
	struct bmi160_reg_int_context *ctx = &state->reg_int_ctx;

	if (ctx->avail.bits.status_0 && (ctx->int_status_0 & BMI160_INT_STATUS_0_D_TAP_INT)) {

		sample_dt =
			sns_dd_bmi160_get_tap_dir(ctx->int_status_2);
		BMI160_MSG_2(ERROR,
				"[handle_irq_dt] DT interrupt detected @timestamp = %d int_status_2: 0x%x",
				ts_irq, ctx->int_status_2);

		bmi160_reset_int(state->port_handle);

		/*! Notify the SMGR of a doubletap event*/
		data_dt = &state->sensor_data_cache_dt;
		data_dt->timestamp = timestamp;
		data_dt->samples[0].sample = sample_dt;

		sub_dev = sns_dd_bmi160_get_subdev_from_type(state,
				SNS_DDF_SENSOR_DOUBLETAP);

		if ((sub_dev) && sub_dev->smgr_handle) {
			status = sns_ddf_smgr_notify_data(sub_dev->smgr_handle,
					data_dt, 1);
			BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
		}
	}

	return SNS_DDF_SUCCESS;
}
#endif

static sns_ddf_status_e sns_dd_bmi160_handle_irq_md(
		sns_dd_bmi160_state_t           *state,
		sns_ddf_time_t                  ts_irq)
{
	bmi160_sub_dev_t *sub_dev;
	struct bmi160_reg_int_context *ctx = &state->reg_int_ctx;

	if (ctx->avail.bits.status_0 && (ctx->int_status_0 & BMI160_INT_STATUS_0_ANYM_INT)) {
		BMI160_MSG_1(ERROR,
				"[handle_irq_md] MD interrupt detected @timestamp = %d",
				ts_irq);

		sub_dev = sns_dd_bmi160_get_subdev_from_type(state,
				SNS_DDF_SENSOR_ACCEL);
		/*! Notify manager of MOTION DETECT event */
		if (sub_dev) {
			sns_ddf_smgr_notify_event(sub_dev->smgr_handle,
					SNS_DDF_SENSOR_ACCEL,
					SNS_DDF_EVENT_MOTION);
#if BMI160_CONFIG_ENABLE_LOG_DATA_L0
			BMI160_MSG_0(ERROR, "event: SNS_DDF_EVENT_MOTION");
#endif
		}
	}

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_bmi160_handle_irq_drdy(
		sns_dd_bmi160_state_t           *state,
		sns_ddf_time_t                  ts_irq)
{
	sns_ddf_status_e status;
	sns_ddf_sensor_sample_s *samples;

	struct bmi160_sensor_data_raw_buf       sensor_data_buf = {{0}};
	union bmi160_sensor_data_req            sensor_data_req = {.req = 0};
	union bmi160_status_reg                 stat_reg = {.reg = 0};
	bmi160_sub_dev_t                        *sub_dev;
	uint32_t                                ts_dev_data;
	sns_ddf_time_t                          ts_cor;

	bmi160_parse_reg_status(state->reg_int_ctx.status, &stat_reg);

	BMI160_MSG_4(HIGH, "[handle_irq_drdy] <0x%02x %d %d %d>",
			stat_reg.reg,
			stat_reg.bits.drdy_acc,
			stat_reg.bits.drdy_gyr,
			stat_reg.bits.drdy_mag);


	if (state->int_en_flags.bits.drdy.bits.acc && stat_reg.bits.drdy_acc) {
#if 0
		sns_ddf_time_t elapse;
		sns_ddf_time_t itvl;
		bmi160_hw_mod_t *hw_mod;

		hw_mod = sns_dd_bmi160_get_hw_mod_cache_acc(state);
		elapse = (int32_t)ts_irq - (int32_t)state->sensor_data_cache_a.timestamp;
		if (hw_mod) {
			itvl = BMI160_SSC_US_2_TICKS(1e6 / state->odr_acc_req);

			BMI160_MSG_3(HIGH, "[handle_irq_drdy] <%d %d %d>",
					(int32_t)state->sensor_data_cache_a.timestamp,
					ts_irq, state->odr_acc_req);
			BMI160_MSG_3(HIGH, "[handle_irq_drdy] <elapse: %d itvl: %d (%d)>",
					elapse, itvl,
					BST_TIME_ELAPSE_NEAR_ITVL(elapse, itvl));
			BMI160_MSG_2(HIGH, "[handle_irq_drdy] <%d %d>)",
					BST_ABS(elapse - itvl), (itvl >> 5));


			if ((elapse > itvl) || BST_TIME_ELAPSE_NEAR_ITVL(elapse, itvl) || (elapse < 0)) {
				sensor_data_req.bits.a = true;
			}
		}
#else
		sensor_data_req.bits.a = true;
#endif
	}

	if (state->int_en_flags.bits.drdy.bits.gyr && stat_reg.bits.drdy_gyr) {
		sensor_data_req.bits.g = true;
	}

#if BMI160_CONFIG_ENABLE_MAG_IF
	if (state->int_en_flags.bits.drdy.bits.mag && stat_reg.bits.drdy_mag) {
		sensor_data_req.bits.m = true;
	}
#endif

	if (sensor_data_req.req) {
		status = bmi160_read_data(state->port_handle, &sensor_data_buf, &sensor_data_req);
	}

	bmi160_parse_data_ts(sensor_data_buf.buf_ts, 3, &ts_dev_data);

	if (state->hw_mod_odr_max) {
		sns_dd_bmi160_get_ts_cor(
				state->hw_mod_odr_max->odr_map_idx,
				state->reg_int_ctx.ts_hw,
				state->reg_int_ctx.ts_sys,
				&ts_cor);
		//LKTD: to read out ts together with data to check for stale data
	} else {
		ts_cor = ts_irq;
	}

	BMI160_MSG_3(HIGH,
			"[handle_irq_drdy] <ts_ctx_sys: %d  ts_ctx_dev: 0x%x ts_cor: %d>",
			state->reg_int_ctx.ts_sys, state->reg_int_ctx.ts_hw, ts_cor);

	if (sensor_data_req.bits.a) {
		sub_dev = sns_dd_bmi160_get_subdev_cache_acc(state);

		if (sub_dev) {
			samples = state->sensor_data_cache_a.samples;

			sns_dd_bmi160_format_data_acc(state, sensor_data_buf.buf_a, samples);

			state->sensor_data_cache_a.timestamp = ts_cor;
			state->sensor_data_cache_a.end_timestamp = ts_cor;

			sns_ddf_smgr_notify_data(sub_dev->smgr_handle, &state->sensor_data_cache_a, 1);

			sns_dd_bmi160_log_data(&state->sensor_data_cache_a, 3, DD_DATA_LOG_CONTEXT_DRI);
		}
	}

	if (sensor_data_req.bits.g) {
		sub_dev = sns_dd_bmi160_get_subdev_cache_gyr(state);
		if (sub_dev) {
			samples = state->sensor_data_cache_g.samples;

			sns_dd_bmi160_format_data_gyr(state, sensor_data_buf.buf_g, samples);
			state->sensor_data_cache_g.timestamp = ts_cor;
			state->sensor_data_cache_g.end_timestamp = ts_cor;
			sns_ddf_smgr_notify_data(sub_dev->smgr_handle, &state->sensor_data_cache_g, 1);

			sns_dd_bmi160_log_data(&state->sensor_data_cache_g, 3, DD_DATA_LOG_CONTEXT_DRI);
		}
	}

#if BMI160_CONFIG_ENABLE_MAG_IF
	if (sensor_data_req.bits.m) {
		sub_dev = sns_dd_bmi160_get_subdev_cache_mag(state);
		if (sub_dev) {
			samples = state->sensor_data_cache_m.samples;

			sns_dd_bmi160_format_data_mag(state, sensor_data_buf.buf_m, samples);
			state->sensor_data_cache_m.timestamp = ts_cor;
			state->sensor_data_cache_m.end_timestamp = ts_cor;
			sns_ddf_smgr_notify_data(sub_dev->smgr_handle, &state->sensor_data_cache_m, 1);

			sns_dd_bmi160_log_data(&state->sensor_data_cache_m, 3, DD_DATA_LOG_CONTEXT_DRI);
		}
	}
#endif
	BST_IGNORE_WARNING_UNUSED_VAR(status);

	return SNS_DDF_SUCCESS;
}

static sns_ddf_status_e sns_dd_bmi160_handle_irq_ff_wml(
		sns_dd_bmi160_state_t           *state,
		sns_ddf_time_t                  ts_irq)
{
	sns_ddf_status_e status = SNS_DDF_SUCCESS;
	struct bmi160_fifo_status ff_status = {0};
	uint8_t         regv;

	uint16_t        ff_count = 0;

	bmi160_sub_dev_t *sub_dev_acc   = sns_dd_bmi160_get_subdev_cache_acc(state);
	if (sub_dev_acc == NULL) {
	   return SNS_DDF_EINVALID_PARAM;
	}
	bmi160_sub_dev_t *sub_dev_gyr   = sns_dd_bmi160_get_subdev_cache_gyr(state);
	if (sub_dev_gyr == NULL) {
	   return SNS_DDF_EINVALID_PARAM;
	}
#if BMI160_CONFIG_ENABLE_MAG_IF
	bmi160_sub_dev_t *sub_dev_mag   = sns_dd_bmi160_get_subdev_cache_mag(state);
	if (sub_dev_mag == NULL) {
	   return SNS_DDF_EINVALID_PARAM;
	}
#endif

	if (!BMI160_CHIP_REV_IS_A2(state->chip_rev)) {
		status = bmi160_get_reg_fifo_count(state->port_handle, &ff_count);
		BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	} else {
		ff_count = state->ff_suggested_bytes2read;
	}

	state->ts_ff_irq = ts_irq;

	if (state->ff_wmi_missing_possible) {
		regv = state->regv_int_map_1;
		regv = BST_CLR_VAL_BIT(regv, 6);
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_INT_MAP_1,
				&regv, 1);
	}

	if (ff_count > 0) {
		status = sns_dd_bmi160_fifo_read_out_frames(state,
				ff_count, true, false, &ff_status);
		if (ff_status.ff_err) {
			//FIXME
			return SNS_DDF_EINVALID_DATA;
		}

		if (ff_status.ff_overflow) {
			if (state->ff_wml_req_acc > 0) {
				status = sns_ddf_smgr_notify_event(sub_dev_acc->smgr_handle,
						SNS_DDF_SENSOR_ACCEL,
						SNS_DDF_EVENT_FIFO_OVERFLOW);

				BMI160_MSG_0(ERROR, "WARNING!!! event: SNS_DDF_EVENT_FIFO_OVERFLOW");
			}

			if (state->ff_wml_req_gyr > 0) {
				status = sns_ddf_smgr_notify_event(sub_dev_gyr->smgr_handle,
						SNS_DDF_SENSOR_GYRO,
						SNS_DDF_EVENT_FIFO_OVERFLOW);

				BMI160_MSG_0(ERROR, "WARNING!!! event: SNS_DDF_EVENT_FIFO_OVERFLOW");
			}

#if BMI160_CONFIG_ENABLE_MAG_IF
			if (state->ff_wml_req_mag > 0) {
				status = sns_ddf_smgr_notify_event(sub_dev_mag->smgr_handle,
						SNS_DDF_SENSOR_MAG,
						SNS_DDF_EVENT_FIFO_OVERFLOW);

				BMI160_MSG_0(ERROR, "WARNING!!! event: SNS_DDF_EVENT_FIFO_OVERFLOW");
			}
#endif
		}

		if (ff_status.ff_rdy_acc) {
			status = sns_ddf_smgr_notify_event(sub_dev_acc->smgr_handle,
					SNS_DDF_SENSOR_ACCEL,
					SNS_DDF_EVENT_FIFO_WM_INT);

			status = sns_ddf_smgr_notify_data(sub_dev_acc->smgr_handle,
					&state->ff_cache_a, 1);

			sns_dd_bmi160_log_data(&state->ff_cache_a, 3, DD_DATA_LOG_CONTEXT_FIFO_WMI);
		}

		if (ff_status.ff_rdy_gyr) {
			status = sns_ddf_smgr_notify_event(sub_dev_gyr->smgr_handle,
					SNS_DDF_SENSOR_GYRO,
					SNS_DDF_EVENT_FIFO_WM_INT);

			status = sns_ddf_smgr_notify_data(sub_dev_gyr->smgr_handle,
					&state->ff_cache_g, 1);
			sns_dd_bmi160_log_data(&state->ff_cache_g, 3, DD_DATA_LOG_CONTEXT_FIFO_WMI);
		}

#if BMI160_CONFIG_ENABLE_MAG_IF
		if (ff_status.ff_rdy_mag) {
			status = sns_ddf_smgr_notify_event(sub_dev_mag->smgr_handle,
					SNS_DDF_SENSOR_MAG,
					SNS_DDF_EVENT_FIFO_WM_INT);

			status = sns_ddf_smgr_notify_data(sub_dev_mag->smgr_handle,
					&state->ff_cache_m, 1);
			sns_dd_bmi160_log_data(&state->ff_cache_m, 3, DD_DATA_LOG_CONTEXT_FIFO_WMI);
		}
		//sns_dd_bmi160_log_mag_data(state,
		//state->ff_cache_g.samples[0].timestamp);
#endif
		sns_dd_bmi160_fifo_post_process(state, true, false);
	}

	if (state->ff_wmi_missing_possible) {
		regv = state->regv_int_map_1;
		status = bmi160_sbus_write_wrapper(state->port_handle,
				BMI160_REGA_USR_INT_MAP_1,
				&regv, 1);
	}

	return status;
}

#if DEBUG
static void cd1__________________________________________________dummy()
{
}
#endif

/*!
 *  @brief Called by the SMGR to get data
 *
 *  @detail
 *  Requests a single sample of sensor data from each of the specified
 *    sensors. Data is returned immediately after being read from the
 *    sensor, in which case data[] is populated in the same order it was
 *    requested,
 *
 *  @param[in]  dd_handle    Handle to a driver instance.
 *  @param[in] sensors       List of sensors for which data isrequested.
 *  @param[in] num_sensors   Length of @a sensors.
 *  @param[in] memhandler    Memory handler used to dynamically allocate
 *                           output parameters, if applicable.
 *  @param[out] data         Sampled sensor data. The number of elements
 *                           must match @a num_sensors.
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
//reviewed
static sns_ddf_status_e sns_dd_bmi160_get_data(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensors[],
		uint32_t                num_sensors,
		sns_ddf_memhandler_s    *memhandler,
		sns_ddf_sensor_data_s   *data[])
{
	uint8_t i;
	sns_ddf_status_e        status;
	sns_ddf_sensor_data_s   *data_ptr;
	sns_dd_bmi160_state_t   *state = sns_dd_bmi160_get_dev(dd_handle);
	bmi160_sub_dev_t        *sub_dev;
	sns_ddf_time_t          ts;

	struct bmi160_sensor_data_raw_buf       sensor_data_buf = {{0}};
	union bmi160_sensor_data_req            sensor_data_req = {.req = 0};

	BST_IGNORE_WARNING_UNUSED_VAR(sub_dev);

	/* Sanity check*/
	for (i = 0; i < num_sensors; i++) {
		switch (sensors[i]) {
			case SNS_DDF_SENSOR_ACCEL:
				sensor_data_req.bits.a = true;
				break;
			case SNS_DDF_SENSOR_GYRO:
				sensor_data_req.bits.g = true;
				break;
			case SNS_DDF_SENSOR_MAG:
				sensor_data_req.bits.m = true;
				break;
			case SNS_DDF_SENSOR_TEMP:
				sensor_data_req.bits.t = true;
				break;
			default:
				return SNS_DDF_EINVALID_PARAM;
		}
	}

	status = bmi160_read_data(state->port_handle, &sensor_data_buf, &sensor_data_req);
	BMI160_DD_CHECK_RETVAL(status, SNS_DDF_SUCCESS);
	ts = sns_ddf_get_timestamp();

	sub_dev = sns_dd_bmi160_get_subdev(dd_handle);

	if ((data_ptr = sns_ddf_memhandler_malloc_ex(memhandler,
					num_sensors * sizeof(sns_ddf_sensor_data_s),
					sub_dev->smgr_handle))
			== NULL) {
		return SNS_DDF_ENOMEM;
	}

	*data = data_ptr;

	for (i = 0; i < num_sensors; i++) {
		data_ptr[i].sensor = sensors[i];
		data_ptr[i].status = SNS_DDF_SUCCESS;
		data_ptr[i].timestamp = ts;

		if (SNS_DDF_SENSOR_ACCEL == sensors[i]) {
			if ((data_ptr[i].samples =
						sns_ddf_memhandler_malloc_ex(memhandler,
							SDD_ACC_NUM_AXIS * sizeof(sns_ddf_sensor_sample_s),
							sub_dev->smgr_handle))
					== NULL) {
				return SNS_DDF_ENOMEM;
			}

			sns_dd_bmi160_format_data_acc(state, sensor_data_buf.buf_a, data_ptr[i].samples);

			state->test_inertial_in_progress = 1;
			if (state->test_inertial_in_progress) {
				BMI160_MSG_3(HIGH, "[get_data_for_inertial_test] acc <%d %d %d>",
						data_ptr[i].samples[0].sample,
						data_ptr[i].samples[1].sample,
						data_ptr[i].samples[2].sample);
			}

			//TODO: resume after knowledge of the delay required for BW settling
#if 0
			// If the timer is still pending, invalidate the data
			if (state->bw_timer_pending) {
				DDF_MSG_1(HIGH, "BMI160 - Invalidating sample at time: %u", ts);
				// Note: the status values for each samples[i] is UNUSED
				data_ptr[i].samples[0].status = SNS_DDF_EINVALID_DATA;
				data_ptr[i].samples[1].status = SNS_DDF_EINVALID_DATA;
				data_ptr[i].samples[2].status = SNS_DDF_EINVALID_DATA;
				data_ptr[i].status = SNS_DDF_EINVALID_DATA;
			} else {
				data_ptr[i].samples[0].status = SNS_DDF_SUCCESS;
				data_ptr[i].samples[1].status = SNS_DDF_SUCCESS;
				data_ptr[i].samples[2].status = SNS_DDF_SUCCESS;
			}
#endif
			data_ptr[i].num_samples = 3;
			sns_dd_bmi160_log_data(&data_ptr[i], 3, DD_DATA_LOG_CONTEXT_POLL);
		} else if (SNS_DDF_SENSOR_GYRO == sensors[i]) {
			if ((data_ptr[i].samples = sns_ddf_memhandler_malloc_ex(memhandler,
							SDD_GYR_NUM_AXIS * sizeof(sns_ddf_sensor_sample_s),
							sub_dev->smgr_handle))
					== NULL) {
				return SNS_DDF_ENOMEM;
			}

			sns_dd_bmi160_format_data_gyr(state, sensor_data_buf.buf_g, data_ptr[i].samples);
			if (state->test_inertial_in_progress) {
				BMI160_MSG_3(HIGH, "[get_data_for_inertial_test] gyr <%d %d %d>",
						data_ptr[i].samples[0].sample,
						data_ptr[i].samples[1].sample,
						data_ptr[i].samples[2].sample);
			}

			data_ptr[i].num_samples = 3;

			sns_dd_bmi160_log_data(&data_ptr[i], 3, DD_DATA_LOG_CONTEXT_POLL);
#if BMI160_CONFIG_ENABLE_MAG_IF
		} else if (SNS_DDF_SENSOR_MAG == sensors[i]) {
			if ((data_ptr[i].samples = sns_ddf_memhandler_malloc_ex(memhandler,
							SDD_MAG_NUM_AXIS * sizeof(sns_ddf_sensor_sample_s),
							sub_dev->smgr_handle))
					== NULL) {
				return SNS_DDF_ENOMEM;
			}

			sns_dd_bmi160_format_data_mag(state, sensor_data_buf.buf_m, data_ptr[i].samples);
			if (state->test_inertial_in_progress) {
				BMI160_MSG_3(HIGH, "[get_data_for_inertial_test] mag <%d %d %d>",
						data_ptr[i].samples[0].sample,
						data_ptr[i].samples[1].sample,
						data_ptr[i].samples[2].sample);
			}

			data_ptr[i].num_samples = 3;
			sns_dd_bmi160_log_data(&data_ptr[i], 3, DD_DATA_LOG_CONTEXT_POLL);
#endif
		} else if (SNS_DDF_SENSOR_TEMP == sensors[i]) {
			if ((data_ptr[i].samples = sns_ddf_memhandler_malloc_ex(memhandler,
							1 * sizeof(sns_ddf_sensor_sample_s),
							sub_dev->smgr_handle))
					== NULL) {
				return SNS_DDF_ENOMEM;
			}

			sns_dd_bmi160_format_data_temp(state, sensor_data_buf.buf_temp,
					data_ptr[i].samples);
			data_ptr[i].samples[0].status = SNS_DDF_SUCCESS;

			data_ptr[i].num_samples = 1;

			sns_dd_bmi160_log_data(&data_ptr[i], 1, DD_DATA_LOG_CONTEXT_POLL);
		}
	}

	return SNS_DDF_SUCCESS;
}


/*===========================================================================

FUNCTION:   sns_dd_bmi160_handle_timer

===========================================================================*/
/*!
 * @brief
 *
 * @detail
 *
 *
 * @param[] :
 *
 */
/*=========================================================================*/
//reviewed
static void sns_dd_bmi160_handle_timer(
		sns_ddf_handle_t dd_handle,
		void* arg)
{
	DDF_MSG_0(MEDIUM, "55555610 - <bmi160_if_ handle_timer> - Handling BW timer...");
	sns_dd_bmi160_state_t *state = sns_dd_bmi160_get_dev(dd_handle);

	state->bw_timer_pending = false;
}


/*!
 *  @brief BMA2x2 interrupt handler
 *
 *  @detail
 *
 *  @return
 *    The error code definition within the DDF
 *    SNS_DDF_SUCCESS on success; Otherwise SNS_DDF_EBUS
 *
 */
static void sns_dd_bmi160_interrupt_handler(
		sns_ddf_handle_t        dd_handle,
		uint32_t                gpio1,
		sns_ddf_time_t          timestamp)
{
	sns_ddf_status_e                status = 0;
	bmi160_int_stat_flag_t          int_stat;

	sns_dd_bmi160_state_t           *state = NULL;
	uint8_t                         si_buf[2]  = "";
	bmi160_sub_dev_t                *sub_dev;

	BMI160_MSG_3_F(ERROR,
			"55555540 - <bmi160_iff_interrupt_handler> dd_handle: %p gpio1: %d timestamp: %d",
			dd_handle, gpio1, timestamp);

	state = (sns_dd_bmi160_state_t *)(dd_handle);

	if (unlikely(gpio1 != state->gpio1)) {
		BMI160_MSG_0(ERROR, "[bmi160_if_interrupt_handler] WARNING!!! false interrupt ignored");
		return;
	}

	status = bmi160_read_reg_int_ctx(state->port_handle,
			&state->int_en_flags,
			&state->reg_int_ctx);

#if BMI160_CONFIG_ENABLE_LOG_DATA_L3
	BMI160_MSG_4(HIGH,
			"[interrupt_handler] en_int_fifo: %d en_int_md: %d en_int_drdy: %d en_int_dt: %d",
			state->int_en_flags.bits.fifo.flag,
			state->int_en_flags.bits.md,
			state->int_en_flags.bits.drdy.flag,
			state->int_en_flags.bits.dt);
#endif

	bmi160_parse_int_stat_flags(&state->reg_int_ctx, &int_stat);

#if BMI160_CONFIG_ENABLE_LOG_DATA_L2
	BMI160_MSG_4(HIGH,
			"[interrupt_handler] istat_fifo: %d istat_md: %d istat_drdy: %d istat_dt: %d",
			int_stat.bits.ff_wml | (int_stat.bits.ff_full << 1),
			int_stat.bits.md,
			int_stat.bits.drdy,
			int_stat.bits.dt);
#endif
	if (unlikely(status)) {
		BMI160_MSG_1(ERROR, "ERROR: %d", status);
		return;
	}

	if (state->int_en_flags.bits.fifo.flag
			&& (int_stat.bits.ff_wml || int_stat.bits.ff_full)
	   ) {
		status = sns_dd_bmi160_handle_irq_ff_wml(state, timestamp);
	}

	if (state->int_en_flags.bits.drdy.flag) {
		//int_stat.bits.drdy is zero, and should not be used
		status = sns_dd_bmi160_handle_irq_drdy(state, timestamp);
	}

	if (state->int_en_flags.bits.md
			&& int_stat.bits.md
	   ) {
		status = sns_dd_bmi160_handle_irq_md(state, timestamp);
	}

#if BMI160_CONFIG_ENABLE_INT_DOUBLE_TAP
	if (state->int_en_flags.bits.dt
			&& int_stat.bits.dt
	   ) {
		status = sns_dd_bmi160_handle_irq_dt(state, timestamp);
	}
#endif

	//TODO: improve by detecting the false interrupt
	if (state->odr_tem_req > 0) {
		if (!(int_stat.bits.drdy
					|| int_stat.bits.ff_wml
					|| int_stat.bits.ff_full)) {
			return;
		}

		sub_dev = sns_dd_bmi160_get_subdev_from_type(state, SNS_DDF_SENSOR_TEMP);
		if (!sub_dev) {
			return;
		}

		status = bmi160_sbus_read_wrapper(state->port_handle,
				BMI160_REGA_USR_TEMPERATURE_0,
				si_buf, 2);
		if (SNS_DDF_SUCCESS != status) {
			return;
		}

		sns_dd_bmi160_format_data_temp(state, si_buf,
				state->sensor_data_cache_t.samples);

		state->sensor_data_cache_t.timestamp = timestamp;
		state->sensor_data_cache_t.end_timestamp = timestamp;
		sns_ddf_smgr_notify_data(sub_dev->smgr_handle, &state->sensor_data_cache_t, 1);
		sns_dd_bmi160_log_data(&state->sensor_data_cache_t, 1, DD_DATA_LOG_CONTEXT_DRI);
	}
}

#if BMI160_CONFIG_ENABLE_FIFO
/**
 * @brief Retrieves a set of sensor data. Asynchronous API
 *
 * Requests sample of sensor data from the specified sensor.
 *
 * @note If a sensor has failed or
 *		 isn't available, @a sns_ddf_sensor_data_s.status must be used to
 *		 reflect this status.
 *
 * @param[in]  dd_handle	   Handle to a driver instance.
 * @param[in]  sensor		   sensor for which data is requested.
 *
 * @param[in]  num_samples	   number of samples to retrieve as available. Drain the FIFO if value is set to Zero.
 * @param[in]  trigger now	   trigger nofity fifo data now or
 *		 later when trigger_now is set to true.
 *
 *
 * @return SNS_DDF_SUCCESS	   if data was populated successfully.
 *		   via sns_ddf_smgr_data_notify() or if trigger_now is
 *		   set to false; Otherwise a specific error code is
 *		   returned.
 *
 * @see sns_ddf_data_notify_data() as this will be used to report the data.
 */

sns_ddf_status_e sns_dd_bmi160_trigger_fifo_data(
		sns_ddf_handle_t    dd_handle,
		sns_ddf_sensor_e    sensor,
		uint16_t            num_samples,
		bool                trigger_now)
{
	sns_ddf_status_e status =  SNS_DDF_SUCCESS;
	sns_dd_bmi160_state_t *state = sns_dd_bmi160_get_dev(dd_handle);


	BMI160_MSG_3_F(ERROR,
			"55555600 - <bmi160_if_ trigger_fifo_data> sensor: %d num_samples: %d trigger_now: %d",
			sensor, num_samples, trigger_now);

	if (!trigger_now) {
		return SNS_DDF_SUCCESS;
	}

	status = sns_dd_bmi160_fifo_flush(state, num_samples, 0);

	return status;
}
#endif

static sns_ddf_status_e sns_dd_bmi160_get_data(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensors[],
		uint32_t                num_sensors,
		sns_ddf_memhandler_s    *memhandler,
		sns_ddf_sensor_data_s   *data[]);

static void sns_dd_bmi160_handle_timer(
		sns_ddf_handle_t dd_handle,
		void* arg);

static void sns_dd_bmi160_interrupt_handler(
		sns_ddf_handle_t       dd_handle,
		uint32_t               gpio1,
		sns_ddf_time_t         timestamp);

extern
sns_ddf_status_e sns_dd_bmi160_init(
		sns_ddf_handle_t        *dd_handle_ptr,
		sns_ddf_handle_t        smgr_handle,
		sns_ddf_nv_params_s     *nv_params,
		sns_ddf_device_access_s device_info[],
		uint32_t                num_devices,
		sns_ddf_memhandler_s    *memhandler,
		sns_ddf_sensor_e        *sensors[],
		uint32_t                *num_sensors);

extern
sns_ddf_status_e sns_dd_bmi160_set_attr(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_attribute_e     attrib,
		void                    *value);

extern
sns_ddf_status_e sns_dd_bmi160_get_attr(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_attribute_e     attrib,
		sns_ddf_memhandler_s    *memhandler,
		void                    **value,
		uint32_t                *num_elems);

extern
sns_ddf_status_e sns_dd_bmi160_reset(sns_ddf_handle_t dd_handle);

extern sns_ddf_status_e sns_dd_bmi160_self_test(
		sns_ddf_handle_t        dd_handle,
		sns_ddf_sensor_e        sensor_type,
		sns_ddf_test_e          test_type,
		uint32_t                *err);

extern
sns_ddf_status_e sns_dd_bmi160_probe(
		sns_ddf_device_access_s *device_info,
		sns_ddf_memhandler_s    *memhandler,
		uint32_t                *num_sensors,
		sns_ddf_sensor_e        **sensors);


extern
sns_ddf_status_e sns_dd_bmi160_enable_sched_data(
		sns_ddf_handle_t dd_handle,
		sns_ddf_sensor_e sensor_type,
		bool enable);

extern
sns_ddf_status_e sns_dd_bmi160_trigger_fifo_data(
		sns_ddf_handle_t    dd_handle,
		sns_ddf_sensor_e    sensor,
		uint16_t            num_samples,
		bool                trigger_now);


sns_ddf_driver_if_s SNS_DD_IF_BMI160 =
{
	/* 5555550X */
	.init                 = &sns_dd_bmi160_init,
	/* 5555551X */
	.get_data             = &sns_dd_bmi160_get_data,
	/* 5555552X */
	.set_attrib           = &sns_dd_bmi160_set_attr,
	/* 5555553X */
	.get_attrib           = &sns_dd_bmi160_get_attr,
	/* 5555554X */
	.handle_timer         = &sns_dd_bmi160_handle_timer,
	/* 5555555X */
	.handle_irq           = &sns_dd_bmi160_interrupt_handler,
	/* 5555556X */
	.reset                = &sns_dd_bmi160_reset,
	/* 5555557X */
	.run_test             = &sns_dd_bmi160_self_test,
	/* 5555558X */
	.enable_sched_data    = &sns_dd_bmi160_enable_sched_data,
	/* 5555559X */
	.probe                = &sns_dd_bmi160_probe,
	/* 5555560X */
#if BMI160_CONFIG_ENABLE_FIFO
	.trigger_fifo_data    = &sns_dd_bmi160_trigger_fifo_data
#endif
};

