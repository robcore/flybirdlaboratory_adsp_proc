/** vi: tw=128 ts=3 sw=3 et
@file dog_hal_8974_lpass.c
@brief This file contains the API details for the Dog Services, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2014 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/debugtools/dog/src/dog_hal_8994_lpass.c#4 $
$DateTime: 2014/12/22 14:16:52 $
$Change: 7184280 $
$Author: pwbldsvc $
===============================================================================*/

/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

FUNCTIONS
  HAL_dogEnable
  HAL_dogDisable
  HAL_dogKick
  HAL_dogAutokick
  HAL_dogEnableBark
  HAL_dogDisableBark
  HAL_dogRegisterBark
  HAL_dogIsAutokicking
  HAL_dogForceBite
  HAL_dogInit

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

#include "comdef.h"             /* Definitions for byte, word, etc.     */
#include "HALhwio.h"
#include "dog_hal.h"
#include "dog_hal_8994_lpass.h"
#include "msmhwiobase.h"
#include "DDIInterruptController.h"
#include "DalDevice.h"
#include "DALDeviceId.h"
#include "DALStdErr.h"
#include "err.h"
#include "timer.h"
#include "sys_m_smsm.h"
#include "rcecb.h"
#include "rcinit.h"

#define DOG_ISR                             32
#define DOG_HW_WAKEUP_TIME_SEC              1              // sec period for HAL_dogWakeupTimerCb
#define DOG_STARTUP_GRACE_TIMER_PERIOD_SEC  40             // sec period for HAL_dogStartupGraceFailureCb

/* sclk = 32MHz, 0.03125ms period, 1ms = 32sclk */
//#define MS_TO_SCLK(ms)  ((ms)<<5) /* x32 */

#define DOG_BARK_ENABLE_TIMEOUT_SLCK        0x7E0BF         // ~16133ms
#define DOG_NMI_ENABLE_TIMEOUT_SLCK         0x7F9BF         // ~16333ms
#define DOG_BITE_ENABLE_TIMEOUT_SLCK        0x7FFFF         // ~16383ms Max value the counter can hold
#define DOG_BITE_ENABLE_TIMEOUT_NOW_SLCK    0x0001          // BITE "NOW" 

volatile boolean dog_intentional_timeout_flag = FALSE;

static void HAL_dogStartupSuccessCb(void);
static void HAL_dogStartupGraceFailureCb(timer_cb_data_type);
static void HAL_dogWakeupTimerCb(timer_cb_data_type);

static timer_type timer_hw = { 0 };                        // timer for HAL_dogWakeupTimerCb

/* One time Timer tightly coupled tightly to RCINIT_RCECB_INITGROUPS.
 * A fail safe mechanism to detect RCINIT groups initialization has failed.
 * Its a non deferrable timer. */
static timer_type dog_startup_grace_timer;

static timer_group_type timer_group_d = { 0 };             // dog timer group

static qurt_mutex_t dog_lock_mutex;
static int dog_lock_inited = 0;

static inline void DOG_LOCK_INIT(void)
{
   if (!dog_lock_inited)
   {
      qurt_pimutex_init(&dog_lock_mutex);

      dog_lock_inited = 1;
   }
}

static inline void DOG_LOCK(void)
{
   if (dog_lock_inited)
   {
      qurt_pimutex_lock(&dog_lock_mutex);
   }
}

static inline void DOG_UNLOCK(void)
{
   if (dog_lock_inited)
   {
      qurt_pimutex_unlock(&dog_lock_mutex);
   }
}


/** =====================================================================
* Function:
*     HAL_dogStartupSuccessCb
*
* Description:
*   This function is called after rc group initialization is done.  
*   It clears the timer and de-registers with RCvent for any future events.
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
static void HAL_dogStartupSuccessCb(void)
{
   time_timetick_type remaining_time= 0;

   /* Clear the timer */
   timer_stop(&dog_startup_grace_timer, T_NONE, &remaining_time);

   /* Undefine the timer */
   timer_undef(&dog_startup_grace_timer);

   /* Unregister with RC events */
   rcecb_unregister_name(RCINIT_RCECB_INITGROUPS, HAL_dogStartupSuccessCb);
}

/** =====================================================================
* Function:
*     HAL_dogStartupGraceFailureCb
*
* Description:
*   This function is called when the dog start up grace timer expires.  
*   It results in Error fatal.
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
static void HAL_dogStartupGraceFailureCb(timer_cb_data_type unused)
{
   time_timetick_type remaining_time= 0;

   /* Clear the timer */
   timer_stop(&dog_startup_grace_timer, T_NONE, &remaining_time);

   /* Undefine the timer */
   timer_undef(&dog_startup_grace_timer);

   ERR_FATAL("DOG detects stalled initialization, triage with IMAGE OWNER", 0, 0, 0);

}

/** =====================================================================
* Function:
*     HAL_dogWakeupTimerCb
*
* Description:
*       timer driven function for hardware dog
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
static void HAL_dogWakeupTimerCb(timer_cb_data_type unused)
{
   unsigned int dog_disabled;

   DOG_LOCK();

   HAL_dogIsAutokicking(&dog_disabled);

   if (!dog_disabled)
   {
      HAL_dogKick();
   }

   DOG_UNLOCK();

   MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH, "DOG HW handler executes");
   //MSG_1(MSG_SSID_TMS, MSG_LEGACY_HIGH,"HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR = ​0x%08X", *(volatile unsigned int*)HWIO_LPASS_QDSP6SS_WDOG_STATUS_ADDR);
}

/** =====================================================================
 * Function:
 *     HAL_dogBarkISR
 *
 * Description:
 *     This function is called when the watchdog bark interrupt occurs
 *
 * Parameters:
 *     callback_param : not used
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogBarkISR(unsigned int callback_param)
{
   ERR_FATAL("DOG BARK Starvation %d %d %d",
             HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_IN, // supply BITE timer value
             HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_IN, // supply BARK timer value
             HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_IN   // supply NMI/UNMASKED timer value
            );
}

/** =====================================================================
 * Function:
 *     HAL_dogEnable
 *
 * Description:
 *     This function enables the hardware dog
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogEnable(void)
{
   // SET NMI TIMEOUT
   HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_OUTM(HWIO_LPASS_QDSP6SS_WDOG_NMI_TIME_DATA_BMSK, DOG_NMI_ENABLE_TIMEOUT_SLCK);

   // ENABLE NMI
   HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_BMSK, 1 << HWIO_LPASS_QDSP6SS_WDOG_CTL_WDOG_TO_NMI_EN_SHFT);

   // SET BITE TIMEOUT
   HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUTM(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK, DOG_BITE_ENABLE_TIMEOUT_SLCK);

   // ENABLE WDOG
   HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 1 << HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT);
}

/** =====================================================================
 * Function:
 *     HAL_dogDisable
 *
 * Description:
 *     This function disables the hardware dog
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogDisable(void)
{
   if (!dog_intentional_timeout_flag)
   {
      // DISABLE WDOG
      HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 0 << HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT);
   }
}

/** =====================================================================
 * Function:
 *     HAL_dogKick
 *
 * Description:
 *     This function kicks the hardware dog
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogKick(void)
{
   if (!dog_intentional_timeout_flag)
   {
      HWIO_LPASS_QDSP6SS_WDOG_RESET_OUT(1 << HWIO_LPASS_QDSP6SS_WDOG_RESET_WDOG_RESET_SHFT);
   }
}

/** =====================================================================
 * Function:
 *     HAL_dogAutokick
 *
 * Description:
 *     This function turns on dog autokick
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogAutokick(void)
{
   if (!dog_intentional_timeout_flag)
   {
      // DISABLE WDOG
      HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 0 << HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT);
   }
}

/** =====================================================================
 * Function:
 *     HAL_DogHwTimerAutokick
 *
 * Description:
 *     This function turns on dog autokick by pausing the HW timer 
 *     and disabling the wdog
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_DogHwTimerAutokick(boolean enable_autokick)
{
   unsigned int dog_disabled;

   DOG_LOCK();

   HAL_dogIsAutokicking(&dog_disabled);

   HAL_dogKick();

   /* Check if we are switching the dog_disabled state
    */
   if (dog_disabled != enable_autokick)
   {
      if (enable_autokick)
      {
         /* Now auto-kicking.  Pause Watchdog's hardware timer and Disable WDOG*/
        HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 0 << HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT);
        timer_pause(&timer_hw);
      }
      else
      {
         /* No longer auto-kicking.  Resume watchdog hardware timer and enabled WDOG*/
         timer_resume(&timer_hw);
         HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 1 << HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT);
      }
   }

   DOG_UNLOCK();

}

/** =====================================================================
 * Function:
 *     HAL_dogEnableBark
 *
 * Description:
 *       Enable the watchdog bark timer.
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogEnableBark(void)
{
   // SET BARK TIMEOUT
   HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUTM(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK, DOG_BARK_ENABLE_TIMEOUT_SLCK);
}

/** =====================================================================
 * Function:
 *     HAL_dogDisableBark
 *
 * Description:
 *       Enable the watchdog bark timer.
 *
 * Parameters:
 *     none
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogDisableBark(void)
{
   // SET BARK TIMEOUT "NEVER"
   HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_OUTM(HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK, HWIO_LPASS_QDSP6SS_WDOG_BARK_TIME_DATA_BMSK);
}

/** =====================================================================
 * Function:
 *     HAL_dogRegisterBark
 *
 * Description:
 *     Register an ISR for the watchdog bark interrupt.
 *
 * Parameters:
 *     none
 *
 *
 * Returns:
 *     none
 * =====================================================================  */
void HAL_dogRegisterBark(void)
{
   static DalDeviceHandle* hInthandle;

   if (DAL_SUCCESS != DAL_DeviceAttach(DALDEVICEID_INTERRUPTCONTROLLER, &hInthandle) || NULL == hInthandle)
   {
      ERR_FATAL("Dog cannot register with DAL", 0, 0, 0);
   }

   DalInterruptController_RegisterISR(hInthandle, DOG_ISR, (DALIRQ)HAL_dogBarkISR, 0, DALINTRCTRL_ENABLE_RISING_EDGE_TRIGGER);
}

/** =====================================================================
* Function:
*     HAL_dogIsAutokicking
*
* Description:
*     Check if dog is autokicking i.e wdog is disabled
*
* Parameters:
*     unsigned int status pointer
*
* Returns:
*     pointer set to 1 if autokicking(wdog disabled), set to 0 (wdog enabled) otherwise
* =====================================================================  */
void HAL_dogIsAutokicking(unsigned int* status)
{
   if (NULL != status)
   {
      if (0 != (HWIO_LPASS_QDSP6SS_WDOG_CTL_INM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK) & HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK))
      {
         *status = 0; //wdog is enabled so its NOT "autokicking"
      }
      else
      {
         *status = 1; //wdog is disabled so it is "autokicking"
      }
   }
}

/** =====================================================================
* Function:
*     HAL_dogForceBite
*
* Description:
*       Force the watchdog to bite
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
void HAL_dogForceBite(void)
{
   // SET MINIMUM TIMEOUT
   HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_OUTM(HWIO_LPASS_QDSP6SS_WDOG_BITE_TIME_DATA_BMSK, DOG_BITE_ENABLE_TIMEOUT_NOW_SLCK);

   // ENABLE BITE
   HWIO_LPASS_QDSP6SS_WDOG_CTL_OUTM(HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_BMSK, 1 << HWIO_LPASS_QDSP6SS_WDOG_CTL_ENABLE_SHFT);

   dog_intentional_timeout_flag = TRUE;                                          //Flag to block kicks
}

/** =====================================================================
* Function:
*     HAL_dogInit
*
* Description:
*       Initialize hardware dog
*
* Parameters:
*     none
*
* Returns:
*     none
* =====================================================================  */
void HAL_dogInit(void)
{
   DOG_LOCK_INIT();

   HAL_dogEnableBark();                                                          /* Enable the watchdog bark timer. */

   HAL_dogRegisterBark();                                                        /* Register an ISR for the watchdog bark interrupt. */

   /* Set timer to kick the wdog as deferrable timer to avoid unnecessary wakeup of Q6 */
   timer_group_set_deferrable(&timer_group_d, TRUE);

   if(TE_SUCCESS != timer_def_osal(&timer_hw,
                                  &timer_group_d,
                                  TIMER_FUNC1_CB_TYPE,
                                  HAL_dogWakeupTimerCb, NULL))
   {
       ERR_FATAL( "Dog Timer def failed", 0, 0, 0);
   }

   if(TE_SUCCESS != timer_set_64(&timer_hw,
                                DOG_HW_WAKEUP_TIME_SEC,
                                DOG_HW_WAKEUP_TIME_SEC,
                                T_SEC))
   {
       ERR_FATAL( "Dog Timer set failed", 0, 0, 0);
   }

  HAL_dogEnable();

  HAL_dogKick();

   if (sys_m_smsm_apps_set(SYS_M_SUBSYS2AP_SMSM_ERR_HDL_RDY) != SYS_M_SMP2P_SUCCESS)
   {
      MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH,"ADSP WDT: smp2p bit set did not succeed");
   }
   else 
   {
      MSG(MSG_SSID_TMS, MSG_LEGACY_HIGH, "ADSP WDT: smp2p bit set succeed");
   }

   /* Event indicates startup completes */
   rcecb_register_name(RCINIT_RCECB_INITGROUPS, HAL_dogStartupSuccessCb); 

   /* Define watchdog timer */
   if(TE_SUCCESS != timer_def_osal(&dog_startup_grace_timer, 
                                  &timer_non_defer_group, 
                                  TIMER_FUNC1_CB_TYPE, 
                                  HAL_dogStartupGraceFailureCb, NULL ))
   {
    ERR_FATAL("Dog startup grace Timer def failed", 0, 0, 0);
   }

   /* Set watchdog timer */
   if(TE_SUCCESS != timer_set_64(&dog_startup_grace_timer, 
                                DOG_STARTUP_GRACE_TIMER_PERIOD_SEC, 
                                0, T_SEC ))
   {
    ERR_FATAL("Dog startup grace Timer set failed", 0, 0, 0);
   }
}

