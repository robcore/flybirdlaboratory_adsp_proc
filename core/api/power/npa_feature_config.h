/*==============================================================================
@file npa_feature_config.h

NPA Features; customize this file for codebases that need less or specific
options enabled.

NOTE: Defeaturation is not enabled in the NPA code yet. So this file doesn't
mean a thing and will not affect how NPA is built.

Copyright (c) 2013 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

$Header: //components/rel/core.adsp/2.6.1/api/power/npa_feature_config.h#1 $
============================================================================*/
#ifndef NPA_FEATURE_CONFIG_H
#define NPA_FEATURE_CONFIG_H

/* Define to remove events from NPA */
//#define DEFEATURE_NPA_EVENTS

/* Define to remove async requests from NPA */
//#define DEFEATURE_NPA_ASYNC_CLIENTS

/* Define to remove all WL related things from NPA */
//#define DEFEATURE_NPA_WORKLOOPS

/* Define to remove transactions from NPA */
//#define DEFEATURE_NPA_TRANSACTIONS

#ifdef DEFEATURE_NPA_WORKLOOPS
#define DEFEATURE_NPA_EVENTS
#define DEFEATURE_NPA_ASYNC_CLIENTS
#endif

#endif // NPA_FEATURE_CONFIG_H
