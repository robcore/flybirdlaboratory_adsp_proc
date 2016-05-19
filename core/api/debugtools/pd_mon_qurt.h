#ifndef PD_MON_QURT_H
#define PD_MON_QURT_H
/** vi: tw=128 ts=3 sw=3 et
@file pd_mon_qurt.h
@brief This file contains the API details for the Protection Domain Monitor, API 1.0
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
Qualcomm Confidential and Proprietary.
===============================================================================*/
/*=============================================================================
Edit History
$Header: //components/rel/core.adsp/2.6.1/api/debugtools/pd_mon_qurt.h#1 $
$DateTime: 2014/10/16 12:45:40 $
$Change: 6781644 $
$Author: pwbldsvc $
===============================================================================*/

/**

Requirements

1. The Deliverable shall be partitioned as drop in Build Time components.

2. The Deliverable dependency shall be partitioned between ROOT PD and USER PD
   depending upon Deliverable technology requirements.

3. The Deliverable shall be launched by software supplied by the Deliverable
   Owner. CORE supplied launching mechanisms shall be used with the RCINIT Framework.

Policy

1. Policy shall be to Initialize CORE related User PD required ROOT Drivers
   in RCINIT Framework Groups by CORE [ (ROOT|USER)/RCINIT_GROUP_0 .. (ROOT|USER)/RCINIT_GROUP_1 ]

2. Policy shall be to Allow for User PD launching to occur from ROOT Domain no sooner
   than ROOT/RCINIT_GROUP_2, following CORE dependency. Recommended launching of User PD
   is from ROOT/RCINIT_GROUP_7.

3. Policy shall be to Allow for Operation of ROOT Protection Domain ROOT Drivers
   in RCINIT Framework Groups by Deliverable Owner [ ROOT/RCINIT_GROUP_2 .. ROOT/RCINIT_GROUP_7 ]

4. Policy shall be to Allow for Operation to USER Protection Domain USER Drivers
   in RCINIT Framework Groups by Deliverable Owner [ USER/RCINIT_GROUP_2 .. USER/RCINIT_GROUP_7 ]

USER PD LAUNCHING INSTRUCTIONS

The deliverable owner is responsible to deliver components to both ROOT PD and USER PD
as necessary. CORE software does not retain or track specific application requirements
of a USER PD -- the protection domain is logically a software partition mechanism that
allows the application owner to retain more control over their deliverable.

A User PD is started by an RCINIT Init Function supplied by the deliverable owner. The
following example shows the minimum PD_MON API use required to launch a specific USER PD.
Essentially, the software below is a "driver" init function that bootstraps the USER PD
deliverable image.

SCONS Source, Provided by AUDIO, pd_audio.scons, Launches Audio PD from ROOT PD

if 'USES_RCINIT' in env:
 env.AddRCInitFunc(
  ROOT_IMG, # Executes in ROOT to SPAWN audio
  {
   'sequence_group'             : 'RCINIT_GROUP_7', # Policy Based, No Earlier than RCINIT_GROUP_2
   'init_name'                  : 'pd_audio',
   'init_function'              : 'pd_mon_audio',
  })

C Source, Provided by AUDIO, pd_audio.c, Launches Audio PD from ROOT PD

#include "pd_mon_qurt.h"
void pd_mon_audio(void)
{
PD_MON_RESTART restart = PD_MON_RESTART_ALWAYS;
PD_MON_HANDLE hPDAudio = pd_mon_spawn(&restart, BUILD_TIME_DEFINED_AUDIO_IMAGE_NAME); }
}

In the case of this specific example, the AUDIO technology area will be supplying their
"driver" init function that launches their software in a USER PD. Other specific examples
where a software application can be partitioned and launched could include SENSORS, MPSS,
... any logical software application that is currently running in a Q6 ROOT PD.

*/

#if defined(__cplusplus)
extern "C" {
#endif

/** @addtogroup pd_mon_api */ /** @{ */

/**
API, Typedefs and Enumerations
*/

typedef enum { PD_MON_STATUS_SUCCESS = 0, PD_MON_STATUS_ERROR = -1 } PD_MON_STATUS;

typedef char const* PD_MON_NAME;          /**< Name */

typedef int PD_MON_HANDLE;                /**< Opaque Handle */

typedef int PD_MON_RESTART;               /**< Restart Counter */

#define PD_MON_RESTART_ONCE   1           /**< Restart Once */
#define PD_MON_RESTART_ALWAYS 0x8fffffff  /**< Restart 2 Billion Times */

#define PD_MON_ERROR    ((PD_MON_HANDLE)0) /**< Error Indication (for Comparision) */

typedef enum { PD_DUMP_STATUS_SUCCESS = 0, PD_DUMP_STATUS_ERROR = -1 } PD_DUMP_STATUS;

typedef char const* PD_DUMP_NAME;

typedef int PD_DUMP_HANDLE;

/**
API, INTERMEDIATE, Spawn a Protection Domain with Restart Monitoring
PD_MON_RESTART -- Default Restart Monitoring Counter
PD_MON_NAME -- Pointer to NULL terminated string, name of the Protection Domain
... -- Optional Args
@return
PD_MON_HANDLE -- Error Indication or Protection Domain Handle
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1, 2)))
#endif
PD_MON_HANDLE pd_mon_spawn(PD_MON_RESTART*, PD_MON_NAME const, ...);

/**
API
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
PD_MON_HANDLE pd_mon_spawn_oneshot(PD_MON_NAME domain);

/**
API
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1, 2)))
#endif
PD_MON_HANDLE pd_mon_spawn_restart(PD_MON_NAME domain, PD_MON_RESTART* restart_p);

/**
API
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
PD_MON_HANDLE pd_mon_load(PD_MON_NAME domain);

/**
API
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
PD_MON_HANDLE pd_mon_unload(PD_MON_NAME domain);

/**
API, Runtime Query of Restart Monitoring Counter
PD_MON_HANDLE -- Protection Domain Handle
@return
PD_MON_RESTART -- Restart Monitoring Counter
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(2)))
#endif
PD_MON_STATUS pd_mon_restart_get(PD_MON_HANDLE, PD_MON_RESTART*);

/**
API, Runtime Change of Restart Monitoring Counter
PD_MON_RESTART -- Restart Monitoring Counter
PD_MON_HANDLE -- Protection Domain Handle
@return
PD_MON_HANDLE -- Error Indication or Protection Domain Handle
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(2)))
#endif
PD_MON_STATUS pd_mon_restart_set(PD_MON_HANDLE, PD_MON_RESTART*);

/**
API, pd_mon_init
@param[in] char const* NULL Terminated Device Name
@return
PD_DUMP_HANDLE Opaque Device Handle
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
PD_MON_HANDLE pd_mon_init(PD_MON_NAME name);

/**
API, pd_dump_destroy
@param[in] PD_DUMP_HANDLE Opaque Device Handle
@return
PD_DUMP_STATUS Error Indication
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result))
#endif
PD_DUMP_STATUS pd_mon_destroy(PD_MON_HANDLE handle);

/**
API, pd_dump_init
@param[in] char const* NULL Terminated Device Name
@return
PD_DUMP_HANDLE Opaque Device Handle
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result, nonnull(1)))
#endif
PD_DUMP_HANDLE pd_dump_init(PD_DUMP_NAME name);

/**
API, pd_dump_destroy
@param[in] PD_DUMP_HANDLE Opaque Device Handle
@return
PD_DUMP_STATUS Error Indication
*/
#if (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
__attribute__((warn_unused_result))
#endif
PD_DUMP_STATUS pd_dump_destroy(PD_DUMP_HANDLE handle);

/** @} */ /* end_addtogroup pd_mon_api */

#if defined(__cplusplus)
}
#endif

#endif
