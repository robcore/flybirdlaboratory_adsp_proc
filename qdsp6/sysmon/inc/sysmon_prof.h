/*-----------------------------------------------------------------------
   Copyright (c) 2014 QUALCOMM Technologies, Incorporated.
   All Rights Reserved.
   QUALCOMM Proprietary.
-----------------------------------------------------------------------*/
#ifndef SYSMON_PROF_H
#define SYSMON_PROF_H

//----------------------Prototypes----------------------------------

/*********************************************************************************
 * FUNCTION: sysmon_profiler_init
 * DESCRIPTION:
 *	Sysmon init function. To be called from main/rcinit.
 *********************************************************************************/
void sysmon_profiler_init(void);

/*********************************************************************************
 * FUNCTION: sysmon_enable
 * DESCRIPTION:
 * 		handles enable request from clients or internal state change.
 *********************************************************************************/
void sysmon_enable(void);

/*********************************************************************************
 * FUNCTION: sysmon_disable
 * DESCRIPTION:
 * 		handles disable request from CLIENTs or internal state change.
 *********************************************************************************/
void sysmon_disable(void);

#endif /*SYSMON_PROF_H*/
