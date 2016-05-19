/*========================================================================
Copyright (c) 2010-2012 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm COnfidential and Proprietary
========================================================================= */

/*========================================================================
Edit History

$Header: 

when       who     what, where, why
--------   ---     -------------------------------------------------------
01/10/12   rkc     Created file.
========================================================================== */
/**
@file qurt_elite_signal_group.cpp

@brief This file contains signal utilities.
*/

#include "qurt_elite.h"

typedef struct
{
   qurt_anysignal_t any_signal;
   qurt_allsignal_t all_signal;
   uint32_t signal_type;
   unsigned int is_any_task_waiting;
} qurt_elite_signal_group_t;

extern "C" {

ADSPResult qurt_elite_signal_group_create(void** ppSigGrp, uint32_t type)
{
   if(!ppSigGrp || 
      !(ANY_SIGNAL_GROUP == type || ALL_SIGNAL_GROUP == type))
   {
      return ADSP_EBADPARAM;
   }

   //temporarily return error for ALL signals since it is not
   //functional in QuRT
   if(ALL_SIGNAL_GROUP == type)
   {
      return ADSP_EBADPARAM;
   }

   qurt_elite_signal_group_t *sig_grp_ptr = (qurt_elite_signal_group_t *)
      qurt_elite_memory_malloc(sizeof(qurt_elite_signal_group_t), QURT_ELITE_HEAP_DEFAULT);

   if(!sig_grp_ptr)
   {
      return ADSP_ENOMEMORY;
   }

   sig_grp_ptr->signal_type = type;
   sig_grp_ptr->is_any_task_waiting = 0;

   if(ANY_SIGNAL_GROUP == sig_grp_ptr->signal_type)
   {
      qurt_anysignal_init(&sig_grp_ptr->any_signal);
   }
   else
   {
      qurt_allsignal_init(&sig_grp_ptr->all_signal);
   }

   *ppSigGrp = (void *)sig_grp_ptr;

   return ADSP_EOK;
}

ADSPResult qurt_elite_signal_group_destroy(void* pSigGrp)
{
   if(!pSigGrp)
   {
      return ADSP_EBADPARAM;
   }

   qurt_elite_signal_group_t *sig_grp_ptr = (qurt_elite_signal_group_t *)pSigGrp;

   //Do not allow deletion if another thread is already waiting on the 
   //signal object.
   if(!qurt_atomic_compare_and_set(&sig_grp_ptr->is_any_task_waiting, 0, 1))
   {
      //another thread is already waiting on this signal object, 
      //so return error
      return ADSP_EBUSY;
   }

   if(ANY_SIGNAL_GROUP == sig_grp_ptr->signal_type)
   {
      qurt_anysignal_destroy(&sig_grp_ptr->any_signal);
   }
   else
   {
      qurt_allsignal_destroy(&sig_grp_ptr->all_signal);
   }

   qurt_elite_memory_free(sig_grp_ptr);

   return ADSP_EOK;
}

ADSPResult qurt_elite_signal_group_set(void* pSigGrp, uint32_t *bit_mask_ptr)
{
   if(!pSigGrp || !bit_mask_ptr)
   {
      return ADSP_EBADPARAM;
   }

   qurt_elite_signal_group_t *sig_grp_ptr = (qurt_elite_signal_group_t *)pSigGrp;

   if(ANY_SIGNAL_GROUP == sig_grp_ptr->signal_type)
   {
      *bit_mask_ptr = (uint32_t) qurt_anysignal_set(&sig_grp_ptr->any_signal, 
                                                    (unsigned int) (*bit_mask_ptr));
   }
   else
   {
      //Broken!!! All signal set should be returning the signal bit mask 
      //before the set operation, per user guide.
      qurt_allsignal_set(&sig_grp_ptr->all_signal, (unsigned int) (*bit_mask_ptr));
   }

   return ADSP_EOK;
}

ADSPResult qurt_elite_signal_group_clear(void* pSigGrp, uint32_t *bit_mask_ptr)
{
   if(!pSigGrp || !bit_mask_ptr)
   {
      return ADSP_EBADPARAM;
   }

   qurt_elite_signal_group_t *sig_grp_ptr = (qurt_elite_signal_group_t *)pSigGrp;

   if(ANY_SIGNAL_GROUP == sig_grp_ptr->signal_type)
   {
      *bit_mask_ptr = (uint32_t) qurt_anysignal_clear(&sig_grp_ptr->any_signal, 
                                                      (unsigned int) (*bit_mask_ptr));
   }
   else
   {
      //Clear API not provided for ALL signal objects. Would this operation be equivalent??
      //This is broken!!!
      qurt_allsignal_wait(&sig_grp_ptr->all_signal, 0);
      *bit_mask_ptr = 0;
   }

   return ADSP_EOK;
}

ADSPResult qurt_elite_signal_group_get(void* pSigGrp, uint32_t* bit_mask_ptr)
{
   if(!pSigGrp || !bit_mask_ptr)
   {
      return ADSP_EBADPARAM;
   }

   qurt_elite_signal_group_t *sig_grp_ptr = (qurt_elite_signal_group_t *)pSigGrp;

   if(ANY_SIGNAL_GROUP == sig_grp_ptr->signal_type)
   {
      *bit_mask_ptr = (uint32_t) qurt_anysignal_get(&sig_grp_ptr->any_signal);
   }
   else
   {
      *bit_mask_ptr = (uint32_t) qurt_allsignal_get(&sig_grp_ptr->all_signal);
   }

   return ADSP_EOK;
}

ADSPResult qurt_elite_signal_group_wait(void* pSigGrp, uint32_t* bit_mask_ptr)
{
   if(!pSigGrp || !bit_mask_ptr)
   {
      return ADSP_EBADPARAM;
   }

   qurt_elite_signal_group_t *sig_grp_ptr = (qurt_elite_signal_group_t *)pSigGrp;

   //Do not allow more than one thread to wait on the signal object
   if(!qurt_atomic_compare_and_set(&sig_grp_ptr->is_any_task_waiting, 0, 1))
   {
      //another thread is already waiting on this signal object, 
      //so return error
      return ADSP_EBUSY;
   }

   if(ANY_SIGNAL_GROUP == sig_grp_ptr->signal_type)
   {
      *bit_mask_ptr = (uint32_t) qurt_anysignal_wait(&sig_grp_ptr->any_signal, 
                                                     (unsigned int) (*bit_mask_ptr));
   }
   else
   {
      //broken!! all signal wait is supposed to return the 
      //set signals mask (per user guide) but the function return type 
      //is actually void in the code.
      qurt_allsignal_wait(&sig_grp_ptr->all_signal, (unsigned int) (*bit_mask_ptr));
   }

   //update that we are finished waiting
   sig_grp_ptr->is_any_task_waiting = 0;

   return ADSP_EOK;
}

} //extern "C" 
