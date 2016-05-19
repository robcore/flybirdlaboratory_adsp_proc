/*==============================================================================

FILE:      ABT_data.c

DESCRIPTION: This file contains target/platform specific configuration data.

PUBLIC CLASSES:  Not Applicable

INITIALIZATION AND SEQUENCING REQUIREMENTS:  N/A
 
Edit History

//#CHANGE - Update when put in the depot
$Header: //components/rel/core.adsp/2.6.1/buses/icb/src/8996/ABT_data.c#1 $ 
$DateTime: 2014/10/16 12:45:40 $
$Author: pwbldsvc $
$Change: 6781644 $ 

When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2013/11/14  tb     Added support for multiple enable/status registers and
                   ported for 8994
2013/04/16  pm     Added interrupt priority  
2012/10/04  av     Support for disabling ABT 
2012/05/31  av     Created
 
        Copyright (c) 2013 Qualcomm Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/
#include "ABTimeout.h"
#include "ABTimeout_HWIO.h"

/*============================================================================
                      TARGET AND PLATFORM SPECIFIC DATA
============================================================================*/

/* Base address for devices */
#define ABT_LPASS0_BASE_ADDR  LPASS_AHBE_TIME_REG_BASE
#define ABT_LPASS1_BASE_ADDR  LPASS_AHBI_TIME_REG_BASE 

/* Bit Mask for ABT Slaves */
#define ABT_LPASS0_BMSK   HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT0_SHFT
#define ABT_LPASS1_BMSK   HWIO_TCSR_TIMEOUT_INTR_STATUS_LPASS_IRQ_OUT_AHB_TIMEOUT1_SHFT

/* ABT Slave CLK Name */
#define ABT_LPASS0_CLK   "audio_wrapper_timeout_clk"
#define ABT_LPASS1_CLK   "audio_core_timeout_clk"

/* Timeout Interrupt Register Address */
#define ABT_TIMEOUT_INTR_LPASS_ENABLE  HWIO_TCSR_TIMEOUT_INTR_LPASS_ENABLE_ADDR
#define ABT_TIMEOUT_INTR_STATUS        HWIO_TCSR_TIMEOUT_INTR_STATUS_ADDR 
#define ABT_TIMEOUT_SLAVE_GLB_EN       HWIO_TCSR_TIMEOUT_SLAVE_GLB_EN_ADDR

/* TCSR Summary Interrupt Vectors */
#define ABT_TCSR_LPASS_INTR_VECTOR     90

/* LPASS Interrupt Priority (Note:  This varies with the processor, as DAL    */
/*                                  passes this through to the underlying     */
/*                                  kernel/OS                                 */
#define ABT_LPASS_INTR_PRIORITY     1


/*============================================================================
                        DEVICE CONFIG PROPERTY DATA
============================================================================*/

/*---------------------------------------------------------------------------*/
/*          Properties data for device ID  = "/dev/ABTimeout"                */
/*---------------------------------------------------------------------------*/

/* ABT Configuration Data*/
static ABT_slave_info_type ABT_cfgdata[] = 
{ 
//ABT_SLAVE_INFO(  name, sl_en, int_en, to_val)
  ABT_SLAVE_INFO(LPASS0,  TRUE,   TRUE,   0xFF),//  LPASS AHBE
  ABT_SLAVE_INFO(LPASS1,  TRUE,   TRUE,   0xFF) //  LPASS AHBI
};

/* ABT interrupt enable array */
static void *intrEnable[] =
{
  (void*)ABT_TIMEOUT_INTR_LPASS_ENABLE,
};

/* ABT interrupt status array */
static void *intrStatus[] =
{
  (void*)ABT_TIMEOUT_INTR_STATUS,
};

/* ABT Platform Data type */
static ABT_platform_info_type ABT_platform_info =
{
    "LPASS",                               /* Image name */
    intrEnable,                               /* INTR Enable address */
    intrStatus,                               /* INTR Status Register address */
    (void*)ABT_TIMEOUT_SLAVE_GLB_EN,       /* ABT Slave global en address */
    ABT_TCSR_LPASS_INTR_VECTOR,            /* ABT TCSR Summary interrupt vector */
    ABT_LPASS_INTR_PRIORITY,               /* ABT LPASS Interrupt priority */
    sizeof(intrEnable)/sizeof(intrEnable[0]), /* Number of interrupt enable/status registers */
};


/* ABT Configuration Property Data*/
ABT_propdata_type ABT_propdata = 
{
    /* Length of the config  data array */
    sizeof(ABT_cfgdata)/sizeof(ABT_slave_info_type), 
    /* Pointer to config data array */ 
    ABT_cfgdata,
    /* Pointer to platform info data */ 
    &ABT_platform_info                                    
};

