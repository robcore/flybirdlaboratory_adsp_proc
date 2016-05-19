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

/*==============================================================================
  DESCRIPTION

  Impelements the driver for the Bosch BMI160 part

  EDIT HISTORY FOR FILE


  when        who      what
  ----------  ---      -----------------------------------------------------------
  03/07/14    Albert    values, odr,  range, power mode, fifo  interrupt of accel, gyr, mag sensor motion detect, double tap interrupt of  accel v0.1
  03/21/14    Albert    self test for acc, gyr and mag  v0.2
  03/28/14    Albert    add initializtions for bmm150   v0.3
  04/02/14    Albert    improve get attr   v0.4
  04/08/14    Albert    add range index   v0.5
  04/17/14    lk        v0.6    : review of draft version v0.5
  04/21/14    lk        v0.6.1  : draft version code review and change,
  05/13/14    lk        v0.7    : first version that fixes all compile errors after review of draft versions
  05/15/14    lk        v1.0    : first very basic version working on ossc: accel + gyro both working in polling mode
  06/07/14    lk        v1.1    : fixed the issue: data of gyro does not get updated
  06/09/14    lk        v1.2    : added FIFO support
  06/12/14    lk        v1.3    : FIFO support works for accel
  06/15/14    lk        v1.3.1  : FIFO support: FIFO configured properly
  06/17/14    lk        v1.3.2  : FIFO support: fix the axes remap issue
  06/24/14    lk        v1.3.3  : FIFO support: fix the SNS_DDF_ATTRIB_FIFO issue
  06/24/14    lk        v1.3.4  : FIFO support: added new algorithm ldt for wml calculation
  06/29/14    lk        v1.3.5  : FIFO support: change the timing for samples
  06/29/14    lk        v1.3.6  : FIFO support: FIFO support works for accel and gyro
  06/29/14    lk        v1.3.7  : add temperature so it works with accel or gyro
  06/29/14    lk        v1.3.8  : add mandatory self test
  06/29/14    lk        v1.3.9  : add data_log_pkt
  06/29/14    lk        v1.3.10 : remove API dependency
  06/29/14    lk        v1.3.11 : use a wrapper for port_read for ease migration to SPI
  07/22/14    lk        v1.3.12 : add delay of power mode transition
  07/23/14    lk        v1.3.13 : add chip id for C2 sample
  07/23/14    lk        v1.3.14 : add chip id for C2 sample
  07/23/14    lk        v1.3.15 : add delay in write wrapper
  07/23/14    lk        v1.3.16 : fix the data corruption issue when fc is bigger than wml
  07/23/14    lk        v1.3.17 : fix the issue that streaming stops when accel and gyro both start
  07/24/14    lk        v1.3.18 : support for self test: OEM, HW/SW
  07/24/14    lk        v1.3.19 : fix some errors in self test
  07/30/14    lk        v1.4.0  : code refactor for uimage support
  07/30/14    lk        v1.4.1  : block data / trace log based on qc's suggestion for uimage mode
  07/30/14    lk        v1.4.2  : code clean up for COMPILE-TIME configurations
  07/30/14    lk        v1.4.3  : uimage fix
  08/07/14    lk        v1.4.4  : uimage fix due to floating point division
  08/09/14    lk        v1.5.0  : add support for double-tap
  08/22/14    lk        v1.5.1  : fix a few warnings by new compiler
  08/22/14    lk        v1.5.2  : double tap
  08/22/14    lk        v1.5.3  : - fix the issue in reset() by removing call to reset_state(),
  				  - doubletap int can be lost due to delay in handle_irq_fifo()
  08/22/14    lk        v1.5.4  : optimize the status register read in interrupt_handler() so the timing is better
  08/26/14    lk        v1.5.5  : fix issue in get_attr_(ATTRIB_ODR)
  08/26/14    lk        v1.5.6  : fix issue in interrupt_handler(), ignore the int_stat.bits.drdy bit for handle_irq_drdy()
  08/27/14    lk        v1.5.7  : add delay after BMI160_REGV_CMD_SOFT_RESET according to spec
  09/01/14    lk        v1.6.0  : uses new APIs: sns_ddf_malloc_ex, sns_ddf_mfree_ex, sns_ddf_memhandler_malloc_ex
  09/01/14    lk        v1.6.1  : uses new APIs: UMSG, UMSG_[1-4]
  09/01/14    lk        v1.7.0  : start debugging of mag slave, files added:
  				  - sns_dd_bmi160_common.h
  				  - sns_dd_bmi160_slave.h
  				  - sns_dd_bmi160_slave_bmm150.c
  				  - sns_dd_bmi160_slave_bmm150_uimg.c
  09/06/14    lk        v1.7.1  : code can compile properly, and mag can show on sensor list
  09/06/14    lk        v1.7.2  : change the prototype of bmi160_sbus_read_wrapper() and bmi160_sbus_write_wrapper() for code size saving
  09/06/14    lk        v1.7.3  : code clean up after refactoring
  09/22/14    lk        v1.7.4  : first basic version with mag data streaming working: mag data are false still
  09/28/14    lk        v1.7.5  : preliminary version for mag support, mag have real values now
  09/28/14    lk        v1.7.6  : use multiplication intead of division for mag data conversion
  09/28/14    lk        v1.7.7  : change slave api: init_private_data();
  09/29/14    lk        v1.8.0  : move enable_sched_data() to big img area
  09/29/14    lk        v1.8.1  : change the MSG SSID to SNS from QDSP6
  09/29/14    lk        v1.8.2  : remove unnecessary delays in sbus_write_wrapper()
  10/02/14    lk        v1.8.3  : change parameter of verify_chip_id() from uint8_t to uint16_t
  10/02/14    lk        v1.8.4  : fix error of position of bmi160_dump_core_reg()
  10/02/14    lk        v1.8.5  : use udelay() instead of mdelay() for slave driver
  10/02/14    lk        v1.8.6  : add adc_resolution_milligauss field
  10/02/14    lk        v1.8.7  : add chip_rev
  10/02/14    lk        v1.8.8  : use edge triggering by default, passed 19hours duration test @fastest rate
  10/02/14    lk        v1.9.0  : fifo_flush()
  10/03/14    lk        v1.9.1  : fifo_flush() before odr change
  10/03/14    lk        v1.9.2  : detailed info for ATTR_DEVICE_INFO
  10/06/14    lk        v1.9.3  : disable dt by default, and fix build error when dt is disabled
  10/06/14    lk        v1.9.4  : disable mag if by default
  10/06/14    lk        v1.9.5  : fix crash issue during init when sensor is not connected (ossc only)
  10/06/14    lk        v1.9.6  : fix typo in ARRAY_SIZE(), and other code clean up
  10/07/14    lk        v1.9.7  : fix compile warnings by new compiler version
  10/15/14    lk        v1.9.8  : match power info to datasheet
  10/15/14    lk        v1.9.9  : fix the sequence of signal_deregister()
  10/16/14    lk        v1.9.10    : fix the typo .r to .l in SNS_DDF_ATTRIB_SUPPORTED_ODR_LIST
  10/16/14    lk        v1.9.11    : sns_dd_bmi160_soft_reset_and_cfg_default()
  10/16/14    lk        v1.9.12    : move data log pkt to uimg code
  10/16/14    lk        v1.9.13    : fix the crash in sns_dd_bmi160_log_data_be()
  10/16/14    lk        v1.9.14    : increase the startup time for testing
  10/16/14    lk        v1.9.15    : add reset() after OEM test is done
  10/21/14    lk        v1.9.16    : change the filename lk_debug.h to sns_dd_bmi160_trace.h
  10/21/14    lk        v1.9.16.1  : call reset_state() in reset() for testing only
  10/27/14    lk        v1.9.17    : fortify support for SPI
  10/27/14    lk        v1.9.18    : centralized data log support
  10/27/14    lk        v1.9.19    : get_attr_odr() for SNS_DDF_SENSOR_TEMP returns the same ODR as major sensor type
  10/27/14    lk        v1.9.20    : fix timing issue after flush_fifo()
  10/30/14    lk        v1.9.21    : fix timing issue after flush_fifo()
  10/31/14    lk        v1.9.22    : fix timing issue after flush_fifo()
  10/31/14    lk        v1.9.23    : improve timing accuracy in handle_irq_drdy()
  11/02/14    lk        v1.10.00   : improve timing accuracy in handle_irq_wml()
  11/02/14    lk        v1.10.01   : minor changes in log
  11/02/14    lk        v1.10.02   : fine-tuning of data logs
  11/11/14    MW        v1.10.03   : eliminate KW error

  INCLUDE FILES

  ============================================================================*/

#ifndef __SNS_DD_BMI160_VER_H
#define __SNS_DD_BMI160_VER_H

#define SNS_DD_MODULE_VER_BMI160 "BMI160_DD_VERSION: 2014/11/11 17:34:00 1.10.03"

#endif

