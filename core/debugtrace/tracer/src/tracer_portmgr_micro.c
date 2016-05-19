/*=============================================================================

FILE:         tracer_portmgr_micro.c

DESCRIPTION:  

================================================================================
            Copyright (c) 2014 Qualcomm Technologies, Inc.
                         All Rights Reserved.
          Qualcomm Technologies Proprietary and Confidential
==============================================================================*/

#include "DALStdErr.h"

#include "tracer_portmgr.h"
#include "tracer_stp.h"

/*---------------------------------------------------------------------------
 * Variable Definitions
 * ------------------------------------------------------------------------*/
boolean bPortMgrInitialized = FALSE;

struct portMgr_s _gPortMgr;

/*---------------------------------------------------------------------------
 * Externalized Function Definitions
 * ------------------------------------------------------------------------*/
STMTracePortType tracer_port_d32(void)
{
   return _gPortMgr.d32Port;
}


