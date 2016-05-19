#ifndef DIAG_LSMI_H
#define DIAG_LSMI_H

/*===========================================================================

                   Diag Mapping Layer DLL , internal declarations

DESCRIPTION
  Internal declarations for Diag Service Mapping Layer.
  

Copyright (c) 2008-2009 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary

===========================================================================*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.adsp/2.6.1/services/diag/LSM/qurt/src/Diag_LSMi.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/05/12   sg      Changes to bring up Diag MultiPD
01/15/09   mad     Moved Synch. Event name prefixes to diag_shared_i.h
09/10/08   mad     Changes for stream driver model. Added WinDiag driver HANDLE 
                   and Synchronization event declarations. Removed Component 
                   Services references.
02/04/08   mad     Created File
===========================================================================*/

/* this process's global file descriptor for diag resource manager */
extern int diag_qdi_handle;

/* This process's pid */
extern int diag_pid;
/* Magic number for lowest value that diag_qdi_handle could have */
#define DIAG_FD_MIN_VALUE 0


#endif /* DIAG_LSMI_H */

