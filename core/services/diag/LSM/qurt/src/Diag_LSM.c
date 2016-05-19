
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              Diag Legacy Service Mapping DLL

GENERAL DESCRIPTION

Implementation of entry point and Initialization functions for Diag_LSM.dll.


EXTERNALIZED FUNCTIONS
Diag_LSM_Init
Diag_LSM_DeInit

INITIALIZATION AND SEQUENCING REQUIREMENTS


Copyright (c) 2007-2010, 2012-2014 by QUALCOMM Technologies, Incorporated. All Rights Reserved.
Qualcomm Confidential and Proprietary

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

$Header: //components/rel/core.adsp/2.6.1/services/diag/LSM/qurt/src/Diag_LSM.c#1 $

when       who    what, where, why
--------   ---    ----------------------------------------------------------
07/06/14   ph      Added support for Diag over STM
03/11/14   sr     Resolved compiler warnings
12/23/13   ph     Included header files required to account for removal of ASSERT macro
10/21/13   sr     Init the mutex diag_lsm_ref_count_mutex only once although
                  diag_LSM_init() is called multiple times.
10/10/12   sg     Print the failure cases in Debug Buffer when Diag_LSM_Init is called
07/05/12   sg     Changes to bringup Diag MultiPD
06/29/10   mad    Eliminating TerminateThread() call altogether. If Diag_LSM_RxThread
                  does not exit gracefully in 100ms, do not do anything.
06/28/10   mad    Signalling Diag_LSM_RxThread to exit gracefully. The thread
                  is terminated if it does not return within 100ms.
06/25/10   mad    Minimizing error-window for the case where CreateFile fails:
                  Instead of calling the blanket De-Init(), just reset what is
                  necessary, before returning from Diag_LSM_Init().
                  Also, check for INVALID_HANDLE_VALUE before calling IOCTL
                  in RegisterForMaskChange().
06/24/10   mad    CreateFile() is called for WDG driver, if Handle value
                  is INVALID OR NULL
04/21/10   sg     Inclusion of diag_v.h for diag_client_maskchange()
04/21/10   sg     Fix to close handles after we terminate the thread
04/20/10   sg     Fixing memory leak with ghDiag_Pkt_Process_Event,ghRxThread
12/03/09   sg     CreateThread() change to return HTHREAD, instead of HANDLE
09/16/09   sg     Included diagpkt.h for the definitions of diag packets
                  Tx and RX Max Sizes macros
06/04/09   mad    Closed Registry key in CreateWaitThread() to fix memory leak.
01/22/09   mad    Now calling Diag_LSM_DeInit() from Diag_LSM_Init(), if
                  windiag driver Open() call fails
01/15/09   mad    Added Synch. Event to signal diag thread reg. processing
                  packet from common table(e.g. mask change)
01/15/09   mad    Priority of Rx thread is now equal to diag thread priority
12/03/08   mad    Changes to take out Component services, and use
                   filesystem calls to access windiag driver, for diag
                  stream-driver model. Added an RxThread that waits for
                  mask-change and incoming-packet events.
10/31/08   mad    Fix for crash in Diag_LSM_Log_Init() when Diag_LSM_Init()-DeInit()
                  is called multiple times. Reset global handles etc explicitly to
                  NULL, in Diag_LSM_DeInit(), so they get initialized correctly
                  in the subsequent Diag_LSM_Init() call.
09/03/08   mad    Added reference count to maintain Diag_LSM functionality,
                  when multiple clients in same process call Diag_LSM_Init()
                  and Diag_LSM_DeInit().
04/23/08   JV     Added calls to functions that update masks during bring-up.
                  LSM registers for a mask change during Init.Now calling
                      diagpkt_bindpkt with the UnBind ID during de-init.
04/14/08   JV     Created instance of IDiagPktRsp
03/19/08   JV     Added packet service to init and de-init functions.
02/05/08   mad    Moved declarations for Diag_LSM_Init() and Diag_LSM_DeInit()
                  to Diag_LSM.h. This will enable clients to include
                  Diag_LSM.h and call the functions directly.
01/15/08   mad    Removed explicit linking to a1Host.lib, now using
                  LoadLibrary() and GetProcAddress() to call functions
                  exported by a1Host.dll. This was done to avoid a1Host.dll
                  being loaded implicitly upon loading of Diag_LSM.dll.
11/29/07   mad    Created

===========================================================================*/

/* separating windows-specific includes, in case this file is featurised
and made common later. */

#include "comdef.h"
#include "Diag_LSMi.h"
#include "DiagSvc_Malloc.h"
#include "Diag_LSM_Event_i.h"
#include "Diag_LSM_Log_i.h"
#include "Diag_LSM_Msg_i.h"
#include "diagpkti.h" /* For definition of diag_cmd_rsp */
#include "Diag_LSM_Pkt_i.h"
#include "diag_shared_i.h" /* For different constants */
#include "diagpkt.h"
#include "diag_v.h"
#include "qurt_qdi.h"
#include "qurt.h"
#include "Diag_LSM.h"
#include "diagstub.h"
#include "Diag_LSM_Qdi_wrapper.h"
#include "stdio.h"
#include "atomic_ops_plat.h"
#include "Diag_LSM_stm.h"

/* Action Codes for RegisterForMaskChange() function */
#define MASK_CHANGE_REGISTER     0
#define MASK_CHANGE_DEREGISTER   1
int diag_qdi_handle = -1;
qurt_thread_t  thread_id;
/* This process's receive thread channel ID */

/* This process's pid */
int diag_pid;
/*A reference count to maintain the number of
clients in the same process. This will be used to:
1. Prevent re-initialization if already initialized in the same process
2. Prevent De-Initialization if other clients are still using Diag_LSM
*/
uint32 gnDiag_LSM_Ref_Count = 0;
qurt_mutex_t diag_lsm_ref_count_mutex;
static unsigned int diag_lsm_ref_count_mutex_init = FALSE;
unsigned long long diag_lsm_stack[4096];

/* Internal function declarations*/
static boolean TerminateWaitThread(void);
static boolean CreateWaitThread(void);
static boolean RegisterForMaskChange(uint32 ActionCode);


/*===========================================================================
FUNCTION   Diag_LSM_Init

DESCRIPTION
  Initializes the Diag Legacy Service Mapping Layer.

DEPENDENCIES
  Successful initialization requires Diag driver (windiag.dll) to be loaded and available in the system.
  and accessible in the file system.
  This function can be called multiple times; mutex initialization should happen only once

RETURN VALUE
  FALSE = failure, else TRUE

SIDE EFFECTS
  None

===========================================================================*/

boolean Diag_LSM_Init (byte* pParam)
{
  if(qurt_atomic_compare_and_set(&diag_lsm_ref_count_mutex_init, FALSE, TRUE))
  {
   qurt_rmutex_init(&diag_lsm_ref_count_mutex);
  }
   qurt_rmutex_lock(&diag_lsm_ref_count_mutex);
   if (0 == gnDiag_LSM_Ref_Count)
   {
      diag_pid = qurt_getpid();


     if (0 > diag_qdi_handle)
      {
         diag_qdi_handle = qurt_qdi_open("/dev/diag");

         if(diag_qdi_handle<0)
         {
       printf(" Diag_LSM_Init : QDI open failed\n");
           qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
           return FALSE;
         }
      }

      if(!DiagSvc_Malloc_Init())
      {
        printf("Diag_LSM_Init : SVC malloc failed\n");
        Diag_LSM_DeInit();
        qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
        return FALSE;
      }


     if(!CreateWaitThread())
     {
        printf("Diag_LSM_Init : createwaitthread failed\n");
        Diag_LSM_DeInit();
        qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
        return FALSE;
     }


     if(!Diag_LSM_Log_Init())
     {
        printf("Diag_LSM_Init : lsm log init failed\n");
       Diag_LSM_DeInit();
       qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
       return FALSE;
     }

     if(!Diag_LSM_Event_Init())
     {
       printf("Diag_LSM_Init : lsm event init failed\n");
       Diag_LSM_DeInit();
       qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
       return FALSE;
     }

     if(!Diag_LSM_Msg_Init())
     {
       printf("Diag_LSM_Init : lsm msg init failed\n");
       Diag_LSM_DeInit();
       qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
       return FALSE;
     }

     if(!Diag_LSM_Pkt_Init())
     {
       printf("Diag_LSM_Init : lsm pkt init failed\n");
       Diag_LSM_DeInit();
       qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
       return FALSE;
     }

#ifdef FEATURE_DIAG_STM
     diag_stm_init();
#endif

    if(!RegisterForMaskChange(MASK_CHANGE_REGISTER))
     {
       printf("Diag_LSM_Init : registerformaskchange failed\n");
       Diag_LSM_DeInit();
       qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
       return FALSE;
      }
   } /*end if(!InterlockedCompareExchange(&gnDiag_LSM_Ref_Count,1,0) */
   gnDiag_LSM_Ref_Count += 1;
   qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
   return TRUE;
}                               /* Diag_LSM_Init */

/*===========================================================================

FUNCTION    Diag_LSM_DeInit

DESCRIPTION
  De-Initialize the Diag service.

DEPENDENCIES
  None.

RETURN VALUE
  FALSE = failure, else TRUE.

SIDE EFFECTS
  None

===========================================================================*/

boolean Diag_LSM_DeInit (void)
{
   boolean bReturn = TRUE;
   qurt_rmutex_lock(&diag_lsm_ref_count_mutex);
   if(1 < gnDiag_LSM_Ref_Count)
   {
       //Someone's still using diag, so just count down and go on with business...
     gnDiag_LSM_Ref_Count -= 1;
     qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
     return bReturn;
   }
   else if(0 == gnDiag_LSM_Ref_Count)
   {
     qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
     return TRUE;
   }

   DiagSvc_Malloc_Exit();

   if( !Diag_LSM_Event_DeInit() || !Diag_LSM_Pkt_DeInit() || !Diag_LSM_Log_DeInit() || !Diag_LSM_Msg_DeInit())
      bReturn  = FALSE;

   if(!RegisterForMaskChange(MASK_CHANGE_DEREGISTER))
      bReturn = FALSE;

   if(!TerminateWaitThread())
   {
      bReturn = FALSE;
   }
   if(0 != qurt_qdi_close(diag_qdi_handle))
   {
      bReturn = FALSE;
   }
   diag_qdi_handle = -1;
    //We uninitialized things because it's the last one, so mark this as having 0 references.
   gnDiag_LSM_Ref_Count = 0;
   qurt_rmutex_unlock(&diag_lsm_ref_count_mutex);
   return bReturn;
}     /* Diag_LSM_DeInit */


void Diag_LSM_RxThread(void* parameter)
{
   int return_val = 0;
   byte Req_Buf[DIAG_MAX_RX_PKT_SIZ];
   dword num_bytes_read = 0;
   int status = 0;
   do{
     return_val = diag_lsm_wait_for_event();
     if( return_val &SYNC_EVENT_DIAG_LSM_PKT_IDX)
     {
       num_bytes_read= diag_lsm_read_data(Req_Buf,DIAG_MAX_RX_PKT_SIZ);

       if(num_bytes_read <= DIAG_MAX_RX_PKT_SIZ)
       {
         diagpkt_LSM_process_request((void*)Req_Buf, (uint16)num_bytes_read, NULL, NULL);
       }
     }

     if( return_val & DIAG_EVENTSVC_MASK_CHANGE)
     {
       event_update_mask();
     }
     if( return_val & DIAG_LOGSVC_MASK_CHANGE)
     {
       log_update_mask();
     }
     if( return_val & DIAG_MSGSVC_MASK_CHANGE)
     {
       msg_update_mask();
     }
#ifdef FEATURE_DIAG_STM
     if( return_val & DIAG_STM_MODE_CHANGE )
     {
       diag_stm_update_mode_LSM();
     }
#endif
     if( return_val & DIAG_KILL_RX_THREAD)
     {
         qurt_thread_exit(status);
     }
   }while(1);

}
/*===========================================================================
DESCRIPTION
   Creates synchronization events for incoming packets and mask change.
   Creates the thread that waits on these synchronization events.
===========================================================================*/

 boolean CreateWaitThread(void)
{
   boolean ret = TRUE;
   int ret_value = 0;
   qurt_thread_attr_t tattr;

   unsigned int stackbase;

   stackbase = (unsigned int)diag_lsm_stack;
   qurt_thread_attr_init (&tattr);
   qurt_thread_attr_set_stack_size (&tattr, ((4096*8) -8));
   qurt_thread_attr_set_stack_addr (&tattr, (void*)((stackbase +7) &(~7)) );
   qurt_thread_attr_set_priority (&tattr, DIAG_PRI-1);
   qurt_thread_attr_set_name(&tattr,"DIAG_LSM");
   ret_value =  qurt_thread_create(&thread_id, &tattr,Diag_LSM_RxThread, NULL);

   if(ret_value == QURT_EFAILED )
   {
       ret = FALSE;
   }

   return ret;
}/* CreateWaitThread() */

/*===========================================================================
DESCRIPTION
   Closes synchronization events for incoming packets and mask change.
   Signals the thread (Diag_LSM_RxThread) that waits on these synchronization
   events, to return.
===========================================================================*/
 boolean TerminateWaitThread(void)
{
  int status;
   boolean bReturn = TRUE;
   qurt_qdi_handle_invoke(diag_qdi_handle, DIAG_QDI_KILL_RX_THREAD);

   qurt_thread_join(thread_id,&status);
   return bReturn;
}/* TerminateWaitThread() */

/*===========================================================================
DESCRIPTION
   Used to register/deregister this client process with Diag driver,
   for mask-change synchronization event.
   (Diag Driver adds the event handle corresponding to the unique synch. event
   name to its table, and sets the event when there is a mask change. For
   De-registration, the entry is removed from the list.)
===========================================================================*/
 boolean RegisterForMaskChange(uint32 ActionCode)
{
   boolean status = TRUE;
   if(diag_qdi_handle >= DIAG_FD_MIN_VALUE )
   {
      int IOCtrlCode = DIAG_IOCTL_ERROR ;
      bindpkt_params_per_process* pbind_req_send =
         malloc(sizeof(bindpkt_params_per_process));
      if(pbind_req_send)
      {
         pbind_req_send->count = 1;
         pbind_req_send->cmd_code = 0;
         pbind_req_send->subsys_id = 0;
         pbind_req_send->cmd_code_lo = 0;
         pbind_req_send->cmd_code_hi = 0;
         pbind_req_send->proc_id = 0;
         pbind_req_send->event_id = 0;
         pbind_req_send->log_code = 0;
         pbind_req_send->client_id = diag_pid;
         switch (ActionCode)
         {
            case MASK_CHANGE_REGISTER:
               IOCtrlCode = DIAG_IOCTL_MASK_REG;
               break;
            case MASK_CHANGE_DEREGISTER:
               IOCtrlCode = DIAG_IOCTL_MASK_DEREG;
               break;
            default:
               break;
         }

        if(!diag_lsm_ioctl(IOCtrlCode,(byte *) pbind_req_send, sizeof(bindpkt_params_per_process),NULL,0,NULL))
        {
           status = FALSE;
        }

         free(pbind_req_send);
      }
      else
      {
         status = FALSE;
      }
   }
   else
   {
      status = FALSE;
   }

   return status;
}

