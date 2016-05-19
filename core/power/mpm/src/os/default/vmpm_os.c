/*==========================================================================
 
  FILE:       vmpm_os.c

  OVERVIEW:   This file implements default OS specific functions of MPM driver
              and is expected to be used within MPM driver only.

  DEPENDENCIES: None

                Copyright (c) 2013 - 2014 QUALCOMM Technologies, Inc. (QTI).
                All Rights Reserved.
                Qualcomm Confidential and Proprietary

===============================================================================
$Header: //components/rel/core.adsp/2.6.1/power/mpm/src/os/default/vmpm_os.c#1 $
$DateTime: 2014/10/16 12:45:40 $
=============================================================================*/ 
#include "vmpm_internal.h"              /* MPM driver related files */
#include "DDIInterruptController.h"     /* IC and GPIO related files */
#include "DDITlmm.h"
#include "DDIGPIOInt.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"                  /* General DAL files */
#include "DALSys.h"
#include "CoreVerify.h"
#ifdef UMPM_ISLAND_MODE_ENABLE
#include "umpm_log.h"
#endif

/*==============================================================================
                            FORWARD DECLARATIONS
 =============================================================================*/
static void vmpm_RetriggerIrq(uint32 irqNum);
static void vmpm_RetriggerGpio(uint32 gpioNum);

/*=========================================================================
 *                   INTERNAL DEFINITIONS & DECLARATIONS
 *========================================================================*/

/**
 * Handle for DAL based Interrupt Controller. This will be used for mapping,
 * registering and triggering interrupts.
 */
static DalDeviceHandle *s_mpmDalIcHandle = NULL;

/**
 * Handle for DAL based GPIO controller. It will be used for mapping and 
 * triggering GPIOs.
 */
static DalDeviceHandle *s_mpmDalGpioHandle = NULL;

/** 
 * Data structure for the retrigger functions.
 */
static mpm_retrigger_functions s_vmpmRetriggerFunctions = 
{
  vmpm_RetriggerGpio,
  vmpm_RetriggerIrq,
  vmpm_LogPrintf,
};

/*============================================================================
 *                      INTERNAL FUNCTION DECLARATIONS
 *===========================================================================*/
/**
 * Triggers the GPIO passed as argument on the master. This function usually
 * called by vmpm_TriggerInterrupts while coming out of sleep if it finds
 * particular GPIO occurred at MPM during sleep.
 *
 * Depending on the implementation, validity of gpioNum may or may not be
 * checked. It is meant for vMPM internal use only.
 *
 * @see vmpm_TriggerInterrupts
 *
 * @param gpioNum: Actual gpio number that will be triggered on the master.
 */
static void vmpm_RetriggerGpio( uint32 gpioNum )
{
  /* Triggering GPIO on the master */
  if( DAL_SUCCESS != GPIOInt_TriggerInterrupt( s_mpmDalGpioHandle, gpioNum ) )
  {
    vmpm_LogPrintf(1, "ERROR: MPM GPIO trigger failed (GPIO: %u)", gpioNum);
    CORE_VERIFY(0);
  }

  return;
}

/**
 * Trigger the interrupt passed as argument on the master. This function 
 * usually called by vmpm_TriggerInterrupts while coming out of
 * sleep if it finds particular interrupt occurred at MPM during 
 * sleep. 
 *
 * Depending on the implementation, validity of gpio_num may or may not be
 * checked. It is meant for vMPM internal use only.
 *
 * @see vmpm_TriggerInterrupts
 *
 * @param irqNum: Local IRQ number for the interrupt that will 
 *                be triggered on the master.
 */
static void vmpm_RetriggerIrq( uint32 irqNum )
{
  /* Triggering interrupt on the master */
  if( DAL_SUCCESS != DalInterruptController_InterruptTrigger(
                         s_mpmDalIcHandle, (DALInterruptID)irqNum ) )
  {
    vmpm_LogPrintf(1, "ERROR: MPM interrupt trigger failed (IRQ: %u)", irqNum);
    CORE_VERIFY(0);
  }

  return;
}

/*=========================================================================
 *                   GLOBAL DEFINITIONS & DECLARATIONS
 *========================================================================*/

/**
 * DAL lock handle for the shared message RAM area. This lock must be
 * acquired whenever Message RAM is being modified.
 */
DALSYSSyncHandle mpmSharedMsgRamLock;

/*
 * vmpm_init
 */
void vmpm_init( void )
{
  uint32 mpmPinNum;
  uint32 gpioNum;

  /* Initializing MPM logging */
  vmpm_LogInit();
#ifdef UMPM_ISLAND_MODE_ENABLE
  umpm_logInit();
#endif

  /* Obtain target specific data */
  vmpm_TargetDataInit();

  /* Get the MPM interrupt controller hardware in a good state. */
  vmpm_HAL_Init(NULL, (uint8 *)vmpm_IrqCfgRegBase_VA, TRUE);

  /* Creating a lock for Shared Message RAM */
  CORE_DAL_VERIFY( DALSYS_SyncCreate(DALSYS_SYNC_ATTR_RESOURCE_INTERRUPT,
                                     &mpmSharedMsgRamLock, NULL) );

  /* Obtaining DAL handle for Interrupt controller */
  CORE_LOG_DAL_VERIFY(
    DAL_DeviceAttach( DALDEVICEID_INTERRUPTCONTROLLER, &s_mpmDalIcHandle ),
    vmpm_LogPrintf( 0, "ERROR: Attaching to Interrupt Controller failed" ) 
  );

  /* Obtaining DAL handle for GPIO controller */
  CORE_LOG_DAL_VERIFY(
    DAL_DeviceAttach( DALDEVICEID_GPIOINT, &s_mpmDalGpioHandle ),
    vmpm_LogPrintf( 0, "ERROR: Attaching to GPIO Controller failed" ) 
  );

  /* Inform the local interrupt controller and GPIO controller of the wakeup 
   * interrupts. Those subsystems will let us know when any of these 
   * interrupts gets enabled, disabled or reconfigured. */
  for( mpmPinNum = 0; mpmPinNum < vmpm_getMapTblSize(); mpmPinNum++ )
  {
    if( MPM_OPEN == vmpm_pinMapTbl[mpmPinNum].mpm_pin_type )
    {
      /* Unmapped interrupt/gpio. Skip this table entry */
      continue;
    }

    if( MPM_SUCCESS == vmpm_getGpioNum(mpmPinNum, &gpioNum) )
    {
      /* Inform about the GPIO wakeup. */
      if( DAL_SUCCESS != 
          GPIOInt_MapMPMInterrupt( s_mpmDalGpioHandle, gpioNum, mpmPinNum ) )
      {
        vmpm_LogPrintf( 3, "ERROR: MPM GPIO mapping failed "
                           "(Handle: 0x%x) (MPM Pin Num: %d) (GPIO ID: %u)",
                           s_mpmDalGpioHandle, 
                           mpmPinNum, 
                           gpioNum );
        CORE_VERIFY(0);
      }
    }
    else if( MPM_SUCCESS == vmpm_IsIrq(mpmPinNum) )
    {
      /* Inform about the IRQ wakeup. */
      if( DAL_SUCCESS != 
          DalInterruptController_MapWakeupInterrupt( s_mpmDalIcHandle, 
             (DALInterruptID)vmpm_pinMapTbl[mpmPinNum].local_pin_num, mpmPinNum ) )
      {
        vmpm_LogPrintf( 3, "ERROR: MPM IRQ mapping failed "
                           "(Handle: 0x%x) (MPM Pin Num: %d) (IRQ Num: %u)",
                           s_mpmDalGpioHandle, 
                           mpmPinNum, 
                           vmpm_pinMapTbl[mpmPinNum].local_pin_num );
        CORE_VERIFY(0);
      }
    }

  }

  /* Determine the number of IRQ's & GPIO's */
  vmpm_setNumMappedIrqs();
  vmpm_setNumMappedGpios();
}

/**
 * vmpm_TriggerInterrupts
 */
void vmpm_TriggerInterrupts(void)
{
  vmpm_retriggerInternal(&s_vmpmRetriggerFunctions);
  return;
}
