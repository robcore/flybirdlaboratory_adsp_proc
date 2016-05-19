/**
@file adsp_lsm_api.h

@brief This file contains all other LSM header files covering service, stream,
session and events. Users need only include this file
for LSM API.
*/

/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.
      Any descriptions that display in the PDF are located in the
      LSM_mainpage.dox file. Contact Tech Pubs for assistance.
===========================================================================*/

/*===========================================================================
Copyright (c) 2014 Qualcomm Technologies, Inc.
All rights reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

/*========================================================================
  Edit History

  $Header: //components/rel/avs.adsp/2.6.1/api/listen/inc/adsp_lsm_api.h#3 $

  when       who     what, where, why
  --------   ---     -------------------------------------------------------
  12/09/2014 sw      (Tech Pubs) Edited Doxygen comments for 2.6.
  07/14/2014 Unni    Introduced support for LSM Topology
==============================================================================*/

#ifndef _ADSP_LSM_API_H_
#define _ADSP_LSM_API_H_

/* Version of the aDSP LSM service.
*/
#define ADSP_LSM_VERSION    0x10000002
/* 0x00000000 : Initail Version
   0x10000001 : Support for Topology introduced
   0x10000002 : Support for Look Ahead Buffering*/

#include "adsp_lsm_session_commands.h"
#include "adsp_lsm_service_commands.h"
#include "adsp_lsm_data_commands.h"
#endif /*_ADSP_LSM_API_H_*/
