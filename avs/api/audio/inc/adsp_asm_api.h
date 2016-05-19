/*========================================================================*/
/**
@file adsp_asm_api.h

@brief This file contains all other ASM header files covering service, stream,
session, data commands and events. Users need only include this file
for ASM API.
*/

/*===========================================================================
Copyright (c) 2010-2012 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
======================================================================== */

/*========================================================================
Edit History

$Header: //components/rel/avs.adsp/2.6.1/api/audio/inc/adsp_asm_api.h#3 $

when       who     what, where, why
--------   ---     -------------------------------------------------------
08/06/12   sw      (Tech Pubs) Updated Doxygen markup to Rev D.2 templates; 
                    updated legal statements for QTI.
05/30/11   sw      (Tech Pubs) Updated Doxygen comments for Interface Spec doc.
04/15/10   rkc      Created file.
========================================================================== */

#ifndef _ADSP_ASM_API_H_
#define _ADSP_ASM_API_H_

/** @ingroup asm_version
    Hexagon ASM version ID.
 */
#define ADSP_ASM_VERSION    0x00070002

#include "adsp_asm_service_commands.h"
#include "adsp_asm_stream_commands.h"
#include "adsp_asm_session_commands.h"
#include "adsp_asm_data_commands.h"

#endif /*_ADSP_ASM_API_H_*/
