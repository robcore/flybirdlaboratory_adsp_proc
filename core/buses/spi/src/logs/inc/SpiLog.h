#ifndef _SPI_LOG_H
#define _SPI_LOG_H

#include "comdef.h"
/*
===========================================================================

FILE:   SpiLog.h

DESCRIPTION:
    This file contains functions data structure declarations for SPI logging
    driver
 
          Copyright (c) 2011-14 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
               Qualcomm Confidential and Proprietary

===========================================================================

        Edit History

$Header: //components/rel/core.adsp/2.6.1/buses/spi/src/logs/inc/SpiLog.h#1 $

When     Who    What, where, why
-------- ---    -----------------------------------------------------------
07/14/12 ag     Include headers common to both EA and DAL environments.
11/02/11 sg     Created

===========================================================================
        Copyright c 2011-2013 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Proprietary/GTDR

===========================================================================
*/

extern int32 SpiLog_Init(void);
/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/
#define SPIDEVICE_LOG_LEVEL_MAX SPIDEVICE_LOG_LEVEL_VERBOSE
#define SPIDEVICE_LOG_LEVEL_VERBOSE 5
#define SPIDEVICE_LOG_LEVEL_INFO 4
#define SPIDEVICE_LOG_LEVEL_WARNING 3
#define SPIDEVICE_LOG_LEVEL_ERROR 2
#define SPIDEVICE_LOG_LEVEL_FATAL_ERROR 1
#define SPIDEVICE_LOG_LEVEL_NONE 0

#define SPIDEVICE_LOG(severity, format_str, args...) 

#endif /* _SPI_LOG_H */

