
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                    VBATT NEW INTERNAL HEADER FILE

GENERAL DESCRIPTION
  This file contains internal vbatt functions to support vbatt interface 
  using PMIC comparator with the Qualcomm Power Management ICs.

Copyright (c) 2008-2010 by Qualcomm Technologies, Incorporated.  All Rights Reserved.

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.adsp/2.6.1/api/systemdrivers/pmic/pm_vbatt.h#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
09/20/10   gh      Add pm_batt_boot_check_if_batt_present API
04/22/10   jtn     Add pm_batt_alarm_hysteresis_set(int hysteresis_us) API
10/22/09   jtn     Add battery threshold APIs to support boot charging
07/26/08   APU     Added the pm_disable_comparator_alarm and
                   pm_enable_comparator_alarm () commands.        			
07/08/08   APU     Tested with 6260, 7201 and added comments
01/02/08   APU     Created.
===========================================================================*/
#ifndef _PM_VBATT_H
#define _PM_VBATT_H
#include "comdef.h"     /* Definitions for byte, word, etc. */
#include "pm_lib_err.h"

#define NUMBER_OF_ITERATIONS_DURING_INIT        15

#define PM_VBATT_COMPARATOR_MAX                 4300
#define PM_VBATT_COMPARATOR_MIN                 2800
#define PM_VBATT_RANGE                  (PM_VBATT_COMPARATOR_MAX-PM_VBATT_COMPARATOR_MIN)

typedef uint16 pm_battery_voltage_type ; 

typedef enum
{
    VBATT_INIT_PASSED = 0 ,
    VBATT_INIT_FAILED 
} vbatt_init_err_type ;       

typedef enum
{
    PMIC_COMPARATOR_VOLTAGE_UP = 0 ,
    PMIC_COMPARATOR_VOLTAGE_DOWN ,
    PMIC_COMPARATOR_VOLTAGE_UNCHANGED 
} pm_comp_window_movement_type ;



/*===========================================================================

FUNCTION pm_did_vbatt_change                            EXTERNAL FUNCTION

DESCRIPTION
  The interrupts informs the driver of any voltage changes. The vbatt task on 
  the other hand services the registered-clients. This function keeps track if 
  "all the clients" have yet been serviced or not. It returns TRUE if the 
  battery voltage has changed and not all clients have registered it.

EXAMPLE:                                               
  if ( pm_did_vbatt_change () )
  { printf ( "Clients have not yet been completely serviced after vbatt a 
  voltage change. " ) ; } 

INPUT PARAMETERS
  NONE.

RETURN VALUE
  Return value type: boolean
  TRUE: vbatt voltage has changed and some or all clients are in the pending 
  list to be serviced.
  FALSE:  After vbatt voltage changed, all clients' were serviced and their 
  callbacks have been called.

  DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  3) vbatt_init()
  4) vbatt_task_init() 
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
boolean pm_dev_did_vbatt_change (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_did_vbatt_change(), which is deprecated. Use pm_dev_did_vbatt_change() instead.")
boolean pm_did_vbatt_change ( void );

/*===========================================================================

FUNCTION pm_vbatt_indicate_task_start                       EXTERNAL FUNCTION

DESCRIPTION
  This function tells the vbatt house-keeping structure that vbatt_task has 
  started and clients can be now serviced.

EXAMPLE:                                               
  if ( pm_vbatt_indicate_task_start () )
  { printf ( "VBATT task has successfully been started by you. " ) ; } 

INPUT PARAMETERS
  NONE.

RETURN VALUE
  Return value type: boolean
  TRUE: vbatt_task has started.
  FALSE: Staring of vbatt_task has failed for some reason.

  DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
boolean pm_dev_vbatt_indicate_task_start (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_vbatt_indicate_task_start(), which is deprecated. Use pm_dev_vbatt_indicate_task_start() instead.")
boolean pm_vbatt_indicate_task_start ( void );



/*===========================================================================

FUNCTION vbatt_init                                         EXTERNAL FUNCTION

DESCRIPTION
  This is the main initialization function for vbatt driver. It accomplishes 
  the following:
  1. Init vbatt data structres.
  2. Sets up PMIC VBATT Comparator.
  3. Sets up the pre-vbatt_task ISR.

NOTE
  1. Make sure that the return value is checked for success.      
  2. Make sure it is only called once, preferably before task initialization.
  EXAMPLE:                                               
  if ( vbatt_init () )
  { printf ( "VBATT Driver init failed ... " ) ; } 

INPUT PARAMETERS
  NONE.

RETURN VALUE
  Return value type: vbatt_init_err_type 
  VBATT_INIT_PASSED : Driver initialization is successful.       
  VBATT_INIT_FAILED FALSE: Driver Init failed. vbatt unusable.

  DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
vbatt_init_err_type vbatt_init ( void ) ;




/*===========================================================================

FUNCTION pm_set_comparator_window EXTERNAL FUNCTION

DESCRIPTION
  pm_set_comparator_window programs PM_BAT_ALRM_THRESH_R_W on the basis of
  pm_calculate_next_window.  

EXAMPLE:                                               
    pm_vbatt_comp_window_change_detector () ;
    pm_set_comparator_window () ;

INPUT PARAMETERS
  NONE.

RETURN VALUE
  NONE.

DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  3) vbatt_init()
  4) vbatt_task_init
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
void pm_dev_set_comparator_window (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_set_comparator_window(), which is deprecated. Use pm_dev_set_comparator_window() instead.")
void pm_set_comparator_window ( void );


/*===========================================================================

FUNCTION pm_vbatt_comp_window_change_detector               EXTERNAL FUNCTION

DESCRIPTION
  pm_vbatt_comp_window_change_detector performs 2 functions:
  1. Checks for direction of voltage change.
  2. Modifies the appropriate data structure to inform that the 
  battery-voltage has changed.

EXAMPLE:                                               
    pm_vbatt_comp_window_change_detector () ;
    (void) pm_set_comparator_window () ;

INPUT PARAMETERS
  NONE.

RETURN VALUE
  NONE.

DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  3) vbatt_init()
  4) vbatt_task_init
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
void pm_dev_vbatt_comp_window_change_detector (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_vbatt_comp_window_change_detector(), which is deprecated. Use pm_dev_vbatt_comp_window_change_detector() instead.")
void pm_vbatt_comp_window_change_detector ( void );



/*===========================================================================

FUNCTION pm_vbatt_voltage_change_registered         EXTERNAL FUNCTION

DESCRIPTION
  Once the voltage is changed, the vbatt_task has the responsibilty of 
  servicing the clients. Before that has been done 
  pm_vbatt_status_voltage.pm_did_batt_voltage_change is set. After the 
  servicing is complete, this flag is reset. 
  This function resets this flag. The caller is vbatt_task, since it services 
  all clients and then calls this function.

EXAMPLE:                                               
  if ( pm_vbatt_voltage_change_registered () )
  { printf ( "VBATT task has serviced all cleints... " ) ; } 

INPUT PARAMETERS
  NONE.

RETURN VALUE
  Return value type: boolean
  TRUE: Servicing pending .
  FALSE: Servicing done.

  DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  3) vbatt_init()
  4) vbatt_task_init()
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
boolean pm_dev_vbatt_voltage_change_registered (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_vbatt_voltage_change_registered(), which is deprecated. Use pm_dev_vbatt_voltage_change_registered() instead.")
boolean pm_vbatt_voltage_change_registered ( void );


/*===========================================================================
FUNCTION pm_comparator_vbatt_read                           EXTERNAL FUNCTION

DESCRIPTION
  This function returns the voltage incident at battery terminals in mV.
         
  EXAMPLE:
  pm_battery_voltage_type batt_voltage = pm_comparator_vbatt_read () ;                           
    
INPUT PARAMETERS
  NONE.

RETURN VALUE
  Return value type: pm_battery_voltage_type 
  Battery voltage between 2800 and 4300 in milli-volts.

DEPENDENCIES
  The following functions must have been called:
  1) rflib_init()
  2) pm_init()
  3) vbatt_init()
  4) vbatt_task_init() 
  
SIDE EFFECTS
  NONE. 
===========================================================================*/
pm_battery_voltage_type pm_dev_comparator_vbatt_read (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_comparator_vbatt_read(), which is deprecated. Use pm_dev_comparator_vbatt_read() instead.")
pm_battery_voltage_type pm_comparator_vbatt_read ( void );

/*===========================================================================

FUNCTION pm_disable_comparator_alarm                           EXTERNAL FUNCTION

DESCRIPTION
 The pm_disable_comparator_alarm clears the interrupt and also disables the 
 disables the Battery Alarm.

EXAMPLE:
 if ( ! pm_disable_comparator_alarm() )
 {
    printf ( "Battery Alarm Disabled " ) ;	
 }

INPUT PARAMETERS
 NONE.
 
RETURN VALUE
 uint8
 0   : Successful
 > 0 : Error Condition. 
 
DEPENDENCIES
 The following functions must have been called:
 1) pm_init()
 2) vbatt_init()

SIDE EFFECTS
 NONE  
===========================================================================*/
pm_err_flag_type pm_dev_disable_comparator_alarm (unsigned pmic_device_index) ;
//#pragma message("Do not use pm_disable_comparator_alarm(), which is deprecated. Use pm_dev_disable_comparator_alarm() instead.")
pm_err_flag_type pm_disable_comparator_alarm ( void );

/*===========================================================================

FUNCTION pm_enable_comparator_alarm                           EXTERNAL FUNCTION

DESCRIPTION
 The pm_enable_comparator_alarm is used enable the Battery Alarm.

EXAMPLE:
 if ( ! pm_enable_comparator_alarm() )
 {
    printf ( "Battery Alarm Enabled " ) ;	
 }

INPUT PARAMETERS
 NONE.
 
RETURN VALUE
 uint8
 0   : Successful
 > 0 : Error Condition. 
 
DEPENDENCIES
 The following functions must have been called:
 1) pm_init()
 2) vbatt_init()

SIDE EFFECTS
 NONE  
===========================================================================*/
pm_err_flag_type pm_dev_enable_comparator_alarm (unsigned pmic_device_index) ; 
//#pragma message("Do not use pm_enable_comparator_alarm(), which is deprecated. Use pm_dev_enable_comparator_alarm() instead.")
pm_err_flag_type pm_enable_comparator_alarm ( void );

/*===========================================================================

FUNCTION pm_batt_alarm_threshold_read                 EXTERNAL FUNCTION

DESCRIPTION
    This function reads the battery voltage status compared against the
preset battery alarm upper and lower voltage threshold when called from 
the bootloader 
                                                                             
INPUT PARAMETERS
    NONE
            
RETURN VALUE
    Return Value Type: int : [-1, 0, 1] 
        -- 1: battery voltage is above the battery alarm upper threshold
              i.e. VBAT > BAT_ALARM_UPPER_THRES
        -- 0: battery voltage is below the battery alarm upper threshold
              and above the battery alarm lower threshold
              i.e. BAT_ALARM_LOWER_THRES < VBAT < BAT_ALARM_UPPER_THRES
        -- -1: battery voltage is below the battery alarm lower threshold 
              i.e. VBAT < BAT_ALARM_LOWER_THRES

DEPENDENCIES
    pm_device_init

SIDE EFFECTS
    NONE

===========================================================================*/
int pm_dev_batt_alarm_threshold_read(unsigned pmic_device_index);
//#pragma message("Do not use pm_batt_alarm_threshold_read(), which is deprecated. Use pm_dev_batt_alarm_threshold_read() instead.")
int pm_batt_alarm_threshold_read(void);

/*===========================================================================

FUNCTION pm_batt_alarm_threshold_set                    EXTERNAL FUNCTION

DESCRIPTION
    This function sets the battery alarm upper and lower voltage threshold 
when called from the bootloader 
                                                                             
INPUT PARAMETERS
    1) Parameter name: lwr_thres
        -- Battery alarm lower voltage threshold in mV
        -- Valid Inputs: 2800 to 4300
            
    2) Parameter name: upr_thres
        -- Battery alarm upper voltage threshold in mV
        -- Valid Inputs: 2800 to 4300

RETURN VALUE
    NONE

DEPENDENCIES
    pm_device_init

SIDE EFFECTS
    NONE

===========================================================================*/
void pm_dev_batt_alarm_threshold_set(unsigned pmic_device_index, uint16 lwr_thresh, uint16 upr_thresh);
//#pragma message("Do not use pm_batt_alarm_threshold_set(), which is deprecated. Use pm_dev_batt_alarm_threshold_set() instead.")
void pm_batt_alarm_threshold_set(uint16 lwr_thresh, uint16 upr_thresh);


/**
 * 
 * @brief API to set the battery alarm time hysteresis
 *
 * 
 * @param hysteresis_us  Hysteresis time in microseconds.  Any value between
 * 125 and 160000 is accepted, however the PMIC API will set the time hysteresis
 * to 125, 250, 500, 1000, 2000, 4000, 8000, or 16000 
 * 
 * @return pm_err_flag_type 
 */
pm_err_flag_type pm_dev_batt_alarm_hysteresis_set(unsigned pmic_device_index, int hysteresis_us);
//#pragma message("Do not use pm_batt_alarm_hysteresis_set(), which is deprecated. Use pm_dev_batt_alarm_hysteresis_set() instead.")
pm_err_flag_type pm_batt_alarm_hysteresis_set(int hysteresis_us);

/*===========================================================================

FUNCTION pm_batt_boot_check_if_batt_present                   EXTERNAL FUNCTION

DESCRIPTION
 This function is used for checking if battery is present during boot.

INPUT PARAMETERS
 Pointer to a boolean where the pointed variable will be set to
 0 - if there is no battery connected
 1 - if battery is connected
 
RETURN VALUE
 uint8
 0   : Successful
 > 0 : Error Condition. 
 
DEPENDENCIES
 The following functions must have been called:
 pm_device_init()

SIDE EFFECTS
 NONE  
===========================================================================*/
pm_err_flag_type  pm_dev_batt_boot_check_if_batt_present(unsigned pmic_device_index, boolean *is_battery_present);
//#pragma message("Do not use pm_batt_boot_check_if_batt_present(), which is deprecated. Use pm_dev_batt_boot_check_if_batt_present() instead.")
pm_err_flag_type  pm_batt_boot_check_if_batt_present(boolean *is_battery_present);

#endif

