/*! \file
 *  
 *  \brief  rpm_settings.c ----This file contains customizable target specific driver settings & PMIC registers.
 *  \details This file contains customizable target specific 
 * driver settings & PMIC registers. This file is generated from database functional
 * configuration information that is maintained for each of the targets.
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation Resource Setting Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Software Register Information Version: VU.Please Provide Valid Label - Not Approved
 *    PMIC code generation Processor Allocation Information Version: VU.Please Provide Valid Label - Not Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *  &copy; Copyright 2010 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/config/msm8x26/pm_lpass_settings.c#1 $ 

when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/07/12   hs      Added support for 5V boost.

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "rpm.h"
#include "pm_lpass_dal.h"

//=======================================================================================

//Mode	            Logic Voltage	Memory Voltage
//Super Turbo	    1.05V	        1.05V
//Turbo	            0.9875V	        1.05V
//Normal	    0.9V	        0.95V
//SVS SOC	    0.8125V	        0.95V
//SVS Krait	    0.725V	        0.95V
//Retention	    0.5V	        0.675V


static unsigned num_of_cx_corners = 6;
static unsigned pm_cx_corners[6] = 
{ 500000, 725000, 812500, 900000, 987500, 1050000};
static char PM_MODEM_CX_VREG[50] = "/pmic/device/smps/A/smps1/vec";

static unsigned num_of_mx_corners = 6;
static unsigned pm_mx_corners[6] = 
{675000, 950000, 950000, 950000, 1050000, 1050000};
static char PM_MODEM_MX_VREG[50] = "/pmic/device/ldo/A/ldo3/vec";

PwrResourceInfoType MX_Info[1] = 
{
    {RPM_LDO_A_REQ,3, &num_of_mx_corners, pm_mx_corners, PM_MODEM_MX_VREG }// data 1 is the size of the LUT, data 2 is the MX LUT, data3 is the RPM resource string 
};
PwrResourceInfoType CX_Info[1] = 
{
    {RPM_SMPS_A_REQ, 1, &num_of_cx_corners, pm_cx_corners, PM_MODEM_CX_VREG }// data 1 is the size of the LUT, data 2 is the CX LUT, data3 is the RPM resource string.
};

