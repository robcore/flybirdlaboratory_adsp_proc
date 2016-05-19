#ifndef IRQAPP_H
#define IRQAPP_H

/*! \file 
*  \n
*  \brief  IrqApp.h ---- PMIC-INTERRUPT MODULE RELATED DECLARATIONS
*  \details  This file contains functions and variable declarations to support 
*   the PMIC4 INTERRUPT module.
*
*
*  \n &copy; Copyright (c) 2003-2011        by Qualcomm Technologies, Inc.  All Rights Reserved.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/api/systemdrivers/pmic/pm_irqs.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/08/11   hw      Merging changes from the PMIC Distributed Driver Arch branch
07/26/10   wra     Changed documentation from @example to Examples so Deoxygen can parse the file
11/06/09   APU     Made the file target independant 
10/20/09   jtn     Move init function prototype to pm_device_init_i.h
06/25/09   jtn     Added "virtual" IRQ handles for SCMM charger
06/17/09   jtn     Branched for SCMM
===========================================================================*/
#include "comdef.h"
#include "pm_lib_err.h"
/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

typedef unsigned short pm_irq_hdl_type ;

/**
 * This type is used for registering PMIC interrupt callback functions.  It is used
 * with the pm_set_irq() API.
 */
typedef void (*pm_isr_ptr_type)(void);

/**
 * This type is used for registering PMIC interrupt callback functions.  It is used
 * with the pm_set_irq_multi_handle()/pm_clear_irq_multi_handle() APIs
 */
typedef void (*pm_isr_ptr_multi_type)(void *);

/*! \enum pm_sec_irq_domain_type
 *  \brief SEC:Secure, MDM:Modem and USR:User interrupts
 */
typedef enum
{
    PM_IRQ_SEC,
    PM_IRQ_MDM,
    PM_IRQ_USR,
    PM_IRQ_DOMAIN_TYPE__INVALID
} pm_sec_irq_domain_type;

/*! \enum pm_irq_trigger_type
 *  \brief PMIC IRQ Trigger types. Enum is based on the 4-bit CONFIG Register field.
 */
typedef enum
{
    PM_IRQ_TRIG_BE        = 0,
    PM_IRQ_TRIG_BE_X      = 1,
    PM_IRQ_TRIG_RE        = 2,
    PM_IRQ_TRIG_HIGH_LVL  = 3,
    PM_IRQ_TRIG_FE        = 4,
    PM_IRQ_TRIG_LOW_LVL   = 5,
    PM_IRQ_TRIG_DISABLE   = 6,
    PM_IRQ_TRIG_DISABLE_X = 7,
    PM_IRQ_CLEAR          = 8,
    PM_IRQ_TRIG_DEFAULT   = 9,
    PM_IRQ_TRIG_INVALID   = 10
} pm_irq_trigger_type;
/**
* IRQ debug ISR type.
*/
typedef void (*pm_isr_debug_func_type)(pm_irq_hdl_type) ;

/*===========================================================================

                      FUNCTION PROTOTYPES

===========================================================================*/
/**
 * 
 * 
 * @brief Register a PMIC interrupt service routine.
 * 
 *     Use this function:
 * 
 *     1) Enable the desired PMIC IRQ and assign to it an
 *        interrupt service routine.
 * 
 *     2) Disable the desired PMIC IRQ by assigning to it a "NULL"
 *        interrupt service routine.
 * @param irq_id  The PMIC IRQ id that is being registered
 * 
 * @param handler The function that will execute when irq_id is triggered
 * 
 * @return pm_err_flag_type
 *         
 *         PM_ERR_FLAG__SUCCESS              = We were successful Enabling/Disabling
 *         the desired PMIC IRQ..
 *         PM_ERR_FLAG__PAR1_OUT_OF_RANGE    = Input Parameter one "pm_irq_hdl" is
 *         out of range.
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED= Feature not available on this
 *         version of the PMIC.
 *         PM_ERR_FLAG__SBI_OPT_ERR          = The SBI driver failed to communicate
 *         with the PMIC.
 * @since 6/1/09
 * 
 * @deprecated New code should use the pm_set_irq_multi_handle
 */
pm_err_flag_type pm_set_irq_handle
(
  pm_irq_hdl_type       irq_id,     
  pm_isr_ptr_type       handler  
);
/**
 * @brief Adds a new ISR handler for irq_id.
 * 
 * Separate calls to this function can add multiple callbacks for the same PMIC 
 * interrupt.
 * @param irq_id      Which IRQ ID
 * 
 * @param handler     The function that will service the IRQ
 * 
 * @param handler_arg Argument to use with handler
 * 
 * @return pm_err_flag_type
 * 
 * Examples
 * - This is a typical IRQ handler function
 * static void    pm_pwr_key_released_isr(void *arg)
 * {
 * ...
 * }
 * 
 * pm_err_flag_type    errFlag    = PM_ERR_FLAG__SUCCESS;
 * 
 * - Clear the interrupt before setting up a handler
 * errFlag |= pm_clear_irq(PM_KPD_PWR_KEY_OFF_IRQ_HDL);
 * 
 * - Set up the IRQ handler
 * errFlag |= pm_set_irq_multi_handle(PM_KPD_PWR_KEY_OFF_IRQ_HDL,
 *                                    pm_pwr_key_released_isr, NULL);
 * if (errFlag != PM_ERR_FLAG__SUCCESS)
 * {
 *    **process error
 * }
 * 
 * - remove one of the handlers for an IRQ
 * errFlag  = pm_clear_irq_multi_handle(PM_KPD_PWR_KEY_OFF_IRQ_HDL,
 *                                      pm_pwr_key_released_isr);
 */
pm_err_flag_type pm_set_irq_multi_handle
(
  pm_irq_hdl_type       irq_id,     
  pm_isr_ptr_multi_type handler,  
  void *handler_arg                 
);
/**
 * 
 * 
 * @brief Remove a handler for one of the PMIC interrupts.
 * 
 * Removes one of the PMIC interrupt handler for a given IRQ ID.
 * @param irq_id  Which IRQ
 * 
 * @param handler The function that was previously registered to service the IRQ.  Since there can be
 *                multiple functions registered for the same IRQ, this function only removes the one
 *                that is equal to "handler"
 * 
 * @return See typedef for pm_err_flag_type
 */
pm_err_flag_type pm_clear_irq_multi_handle
(
  pm_irq_hdl_type       irq_id,     /* Which IRQ */
  pm_isr_ptr_multi_type handler     /* The function that will service the IRQ */
);

/**
 * 
 * 
 * @brief Get the real-time status on a PMIC interrupt
 * 
 * This function returns the current bit-wise (not latch) status of the select
 * PMIC IRQ. Use this function for polling the desired PMIC real time status bit
 * if the IRQ is not enabled. An interrupt will not be trigger until the
 * corresponding IRQ is enable.
 * 
 * @param rt_status_id Which IRQ Real Time Status we want to read
 * 
 * @param rt_status    Pointer to a boolean variable that returns the real time status
 *                     of the selected IRQ.
 *                     TRUE  = Interrupt is triggered
 *                     FALSE = Interrupt is not
 *                     triggered
 * 
 * @return PM_ERR_FLAG__PAR1_OUT_OF_RANGE    = Input Parameter one is out of range.
 *         PM_ERR_FLAG__PAR2_OUT_OF_RANGE    = Input Parameter two is out of range.
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED= Feature not available on this
 *         version of the PMIC.
 *         PM_ERR_FLAG__SBI_OPT_ERR          = The SBI driver failed to communicate
 *         with the PMIC.
 *         PM_ERR_FLAG__SUCCESS              = SUCCESS.
 */
pm_err_flag_type pm_get_rt_status(pm_irq_hdl_type   rt_status_id,
                                  boolean           *rt_status);

/**
 * @brief Find out if an interrupt is triggered.
 * 
 * This function returns the status of the different PMIC
 * IRQs. An interrupt will not be trigger until the corresponding IRQ
 * is enabled. The IRQ status bit will stay active until the corresponding
 * IRQ is cleared.
 * 
 * @param irq_id Which IRQ
 * 
 * @param status Pointer to a boolean variable that returns the status of the selected IRQ.
 *               TRUE = Interrupt is triggered
 *               FALSE = Interrrupt is not triggered
 * 
 * @return     PM_ERR_FLAG__PAR1_OUT_OF_RANGE    = Input Parameter one is out of range.
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED= Feature not available on this
 *         version of the PMIC.
 *         PM_ERR_FLAG__SBI_OPT_ERR          = The SBI driver failed to communicate
 *         with the PMIC.
 *         PM_ERR_FLAG__SUCCESS              = SUCCESS.
 */
pm_err_flag_type pm_get_irq_status(pm_irq_hdl_type irq_id,
                                   boolean         *status);

/**
 * @brief  Reset the selected IRQ
 * 
 * This function resets/clears the selected IRQ.
 * 
 * @param irq_id Which IRQ
 * 
 * @return     PM_ERR_FLAG__PAR1_OUT_OF_RANGE    = Input Parameter one is out of range.
 *         PM_ERR_FLAG__SBI_OPT_ERR          = The SBI driver failed to communicate
 *         with the PMIC.
 *         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED= Feature not available on this
 *         version of the PMIC.
 *         PM_ERR_FLAG__SUCCESS              = SUCCESS.
 */
pm_err_flag_type pm_clear_irq(pm_irq_hdl_type irq);

/**
* @brief  Clears PMIC interrupt handler for a given IRQ ID
* 
* This function may be called more than once to clear multiple callback functions
* for the same IRQ ID..
* 
* @param irq_id Which IRQ
*
* @param handler The function that will service the IRQ
* 
* @return     PM_ERR_FLAG__PAR1_OUT_OF_RANGE    = Input Parameter one is out of range.
*         PM_ERR_FLAG__SBI_OPT_ERR          = The SBI driver failed to communicate
*         with the PMIC.
*         PM_ERR_FLAG__FEATURE_NOT_SUPPORTED= Feature not available on this
*         version of the PMIC.
*         PM_ERR_FLAG__SUCCESS              = SUCCESS.
*/
pm_err_flag_type pm_clear_irq_handle
    (
    pm_irq_hdl_type      irq_id,     /* Which IRQ */
    pm_isr_ptr_type      handler     /* ISR to service the IRQ */
    );


pm_err_flag_type pm_config_irq
(
    pm_irq_hdl_type          irq_id,     /* Which IRQ */
    pm_irq_trigger_type      irq_trigger, /* The trigger type for the IRQ. */
    pm_sec_irq_domain_type   irq_domain,   /* interrupt domain SEC/USR/MDM */
    boolean                  irq_permission /* The permission of the IRQ */
) ;

#endif /* IRQ_APP_H */
