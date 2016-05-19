/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                          Diag GPIO detection for reset.

General Description
  The routines in this file handle configuring, reading, and writing GPIOs
  which are used for communcating DIAG between the MSM and MDM for fusion
  devices.

Copyright (c) 2011, 2013 by QUALCOMM Technologies Incorporated.  All Rights Reserved.
All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                               Edit History

 $Header: //components/rel/core.adsp/2.6.1/services/diag/DCM/common/src/diagreset.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
11/27/13   ph      Updated MSG 1.0 API references to MSG.2.0.
1/11/11   vs    File Created

===========================================================================*/



#include "comdef.h"
#include "customer.h"
#include "diagpkt.h" 

#if defined DIAG_GPIO_INIT

#include "hw.h"
#include "tramp.h"
#include "DDITlmm.h"
#include "DALDeviceId.h"
#include "DDIChipInfo.h"



byte reset_req[] = {41,2,0};
byte offline_req[] = {41,1,0};

#define AP2MDM_STATUS_GPIO 5


#define RESET_AP2MDM_STATUS_GPIO    DAL_GPIO_CFG( AP2MDM_STATUS_GPIO  , 0, DAL_GPIO_INPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA)

#define DIAG_GPIO_TRIGGER TRAMP_TRIGGER_FALLING

static DalDeviceHandle *phChipInfo = NULL;
static DalDeviceHandle *phTLMM = NULL;

typedef enum {
  DIAG_GPIO_UNKNOWN = 0,
  DIAG_GPIO_NORMAL,       
  DIAG_GPIO_FUSION_7K,      
  DIAG_GPIO_FUSION_9K,
  DIAG_GPIO_TOTAL,
} diag_gpio_cfg_type;

typedef enum {
  DIAG_GPIO_MONITOR_UNKNOWN = 0,
  DIAG_GPIO_MONITOR_ENABLE,       
  DIAG_GPIO_MONITOR_DISABLE,      
  DIAG_GPIO_MONITOR_TOTAL,
} diag_gpio_monitor_type;

static diag_gpio_cfg_type diag_gpio_cfg = DIAG_GPIO_UNKNOWN;
static diag_gpio_monitor_type diag_gpio_monitor_status = DIAG_GPIO_MONITOR_UNKNOWN;



static void  reset_gpio_isr( uint32 gpio )
{
    // diag_cmd_req(offline_req,(unsigned int)sizeof(reset_req)/sizeof(byte),NULL,NULL);
  // diag_cmd_req(reset_req,(unsigned int)sizeof(reset_req)/sizeof(byte),NULL,NULL);
  hw_reset(); 

}


boolean diag_gpio_init( void )
{
		DALResult dal_attach = DAL_SUCCESS;
		DalChipInfoFamilyType eFamily = DALCHIPINFO_FAMILY_UNKNOWN;
		hw_platform_type platform;

		if(phTLMM==NULL)
		{
		  dal_attach = DAL_DeviceAttach(DALDEVICEID_TLMM, &phTLMM);
		  if((!phTLMM)||(dal_attach != DAL_SUCCESS))
		  {
			return FALSE;
		  }
		  DalDevice_Open(phTLMM,DAL_OPEN_SHARED);
		}

		if(phChipInfo==NULL)
		{
		  dal_attach = DAL_DeviceAttach(DALDEVICEID_CHIPINFO, &phChipInfo);
		  if((!phChipInfo)||(dal_attach != DAL_SUCCESS))     
		  {
			return FALSE;
		  }
		  DalDevice_Open(phChipInfo, DAL_OPEN_SHARED);
		  DalChipInfo_GetChipFamily(phChipInfo, &eFamily);
		}


  if(eFamily == DALCHIPINFO_FAMILY_MDM9X00)
  {
    
    /* configure MDM Fusion GPIOs here */
    DalTlmm_ConfigGpio( phTLMM,
      (DALGpioSignalType)RESET_AP2MDM_STATUS_GPIO ,                           
      DAL_TLMM_GPIO_ENABLE );
    

    /* Register ISR */
    tramp_gpio_register_isr(AP2MDM_STATUS_GPIO , DIAG_GPIO_TRIGGER , 
      (tramp_handler_type)reset_gpio_isr, AP2MDM_STATUS_GPIO );

    diag_gpio_cfg = DIAG_GPIO_FUSION_9K;
    diag_gpio_monitor_status = DIAG_GPIO_MONITOR_ENABLE;    

  }
  else
  {
    /* No GPIOs to configure */
    diag_gpio_cfg = DIAG_GPIO_NORMAL;
    diag_gpio_monitor_status = DIAG_GPIO_MONITOR_DISABLE;    
  }

  return TRUE;



}

#endif /* DIAG_GPIO_INIT */


