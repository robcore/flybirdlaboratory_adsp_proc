#ifndef PM_LPASS_PROC_NPA_H
#define PM_LPASS_PROC_NPA_H

/*! \file
 *  
 *  \brief  pm_lpass_proc_npa.h ----This file contains prototype definitions processor npa layer
 *  \details This file contains prototype definitions processor npa layer
 *          which consists mainly of the initialization function prototype
 *  
 *    PMIC code generation Version: 1.0.0.0
 *    PMIC code generation NPA Client Version: MSM8x26_PM8026_NPA_2012_10_19 - Approved
 *    PMIC code generation NPA Device Setting Value Version: MSM8x26_PM8026_NPA_2012_10_19 - Approved
 *    This file contains code for Target specific settings and modes.
 *  
 *    &copy; Copyright (c) 2010-2012 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.

$Header: //components/rel/core.adsp/2.6.1/systemdrivers/pmic/npa/inc/pm_lpass_proc_npa.h#1 $ 

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/*===========================================================================

                        DEFINITIONS

===========================================================================*/

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/

/*===========================================================================

                FUNCTION DEFINITIONS

===========================================================================*/

/*===========================================================================

FUNCTION pm_lpass_proc_npa_init

DESCRIPTION
    This function initializes the NPA for lpass.

    It does the following:
    1)  It initializes the PMIC NPA software driver for nodes and resources.

INPUT PARAMETERS
  None.

RETURN VALUE
  None.

DEPENDENCIES
  None.

SIDE EFFECTS
  None.

===========================================================================*/
void pm_lpass_proc_npa_init(void);


#endif //PM_LPASS_PROC_NPA_H



