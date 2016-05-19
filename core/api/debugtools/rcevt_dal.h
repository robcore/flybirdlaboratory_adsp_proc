#ifndef RCEVT_DAL_H
#define RCEVT_DAL_H
/** vi: tw=128 ts=3 sw=3 et
@file rcevt_dal.h
@brief This file contains the API for the Run Control Event Notification, API 2.0
*/
/*=============================================================================
NOTE: The @brief description above does not appear in the PDF.
The tms_mainpage.dox file contains the group/module descriptions that
are displayed in the output PDF generated using Doxygen and LaTeX. To
edit or update any of the group/module text in the PDF, edit the
tms_mainpage.dox file or contact Tech Pubs.
===============================================================================*/
/*=============================================================================
Copyright (c) 2013 Qualcomm Technologies Incorporated.
All rights reserved.
Qualcomm Confidential and Proprietary
=============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/rcevt_dal.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

#include "DALSys.h"
#include "rcevt.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/** @addtogroup rcevt_api @{ */

////////////////////////////////////////
// REGISTER
////////////////////////////////////////

// DALSYSEventHandle hEvent;
// RCEVT_SIGEX_SIGDAL client_sigex;
//
// if (DAL_SUCCESS != DALSYS_EventCreate(DALSYS_EVENT_ATTR_NORMAL, &hEvent, NULL))
// {
// MSG("error"); // handle error
// }
//
// client_sigex.signal = hEvent;
//
// if (RCEVT_NULL == rcevt_register_sigex_name(CLIENT_EVENTNAME, RCEVT_SIGEX_TYPE_SIGDAL, &client_sigex))
// {
// MSG("error"); // handle error
// }

////////////////////////////////////////
// BLOCKING WAIT
////////////////////////////////////////

// if (DAL_SUCCESS != DALSYS_EventWait(hEvent))
// {
// MSG("error"); // handle error
// }
// else
// {
// MSG("event handler");
// }

////////////////////////////////////////
// UNREGISTER
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_unregister_sigex_name(CLIENT_EVENTNAME, RCEVT_SIGEX_TYPE_SIGDAL, &client_sigex))
// {
// MSG("error"); // handle error
// }
//
// if (DAL_SUCCESS != DALSYS_DestroyObject(hEvent))
// {
// MSG("error"); // handle error
// }

////////////////////////////////////////
// SIGNAL FROM OTHER CONTEXT
////////////////////////////////////////

// if (RCEVT_NULL == rcevt_create_name(CLIENT_EVENTNAME)) // Prior to Use
// {
// MSG("error"); // handle error
// }

// if (RCEVT_NULL == rcevt_signal_name(CLIENT_EVENTNAME))
// {
// MSG("error"); // handle error
// }

/**
API, NHLOS Specific Structure
*/
typedef struct
{
   DALSYSEventHandle signal;

} RCEVT_SIGEX_SIGDAL;

/** @} end_addtogroup rcevt_api */

#if defined(__cplusplus)
}
#endif

#endif
