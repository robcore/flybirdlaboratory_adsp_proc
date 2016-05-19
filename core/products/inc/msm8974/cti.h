/*==============================================================================
  FILE:         cti.h
  
  OVERVIEW:     This file provides the externs and declarations needed for
                target specific code

  DEPENDENCIES: None

                Copyright (c) 2012-2013 QUALCOMM Technologies Incorporated.
                All Rights Reserved.
                Qualcomm Confidential and Proprietary
================================================================================
$Header: //components/rel/core.adsp/2.6.1/products/inc/msm8974/cti.h#1 $
$DateTime: 2014/10/16 12:45:40 $
==============================================================================*/
#include "DALStdDef.h"
#include "DDIChipInfo.h"

// Macros
#define CTI_IMEM_1 0xFE805938
#define CTI_IMEM_2 0xFE80593C
#define CTI_IMEM_3 0xFE805940
#define COOKIE_LOCATION         CTI_IMEM_3

#define COOKIE_BUSYWAIT         0x03444248
#define COOKIE_BKRPT            0x03444249
#define COOKIE_CRASH            0x0344424A
#define COOKIE_TRACE            0x0344424B
#define COOKIE_ETM_COMPARATOR   0x0344424C
#define COOKIE_DISABLE_SLEEP    0x0344424D
#define COOKIE_READ_REG         0x0344424E


#define MODEM_SELECT_MASK       0x2
#define ADSP_SELECT_MASK        0x4
#define PROCESSOR_SELECT_MASK   ADSP_SELECT_MASK

typedef struct 
{
  DALSYSWorkLoopHandle    handle;
  DALSYSEventHandle       event;
  
  // Event for trigger infinite loop in the WorkLoop
  DALSYSEventHandle         start_event;
  uint32                    cookie;
  uint32                    processor_select;
  uint32                    cookie_action;
  unsigned int              reg1;
  unsigned int              reg2;
  unsigned int              reg3;
  
} cti_target_config;

//cti_target_config * cti_target_init( void );


static void CTI_Wakeup_Handler(uint32 param);

void cti_irq_init( void );

DALResult cti_workloop(DALSYSEventHandle hEvent, void *pCtx);

void cti_init_workloop( void );

volatile unsigned int cti_read_imem(void);

void cti_read_registers(void);

