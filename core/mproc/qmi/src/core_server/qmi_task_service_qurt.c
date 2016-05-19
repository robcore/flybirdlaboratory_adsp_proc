#include "qmi_task_service.h"
/*---------------------------------------------------------------------------
   QMI_TASK_SERVICE_QURT.C
---------------------------------------------------------------------------*/
/*!
  @file
    qmi_task_service_qurt.c

  @brief
    This file contains the qurt based implementation of task service APIs.

  ---------------------------------------------------------------------------
  Copyright (c) 2012 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
---------------------------------------------------------------------------*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$$

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 

===========================================================================*/



#define QMI_SERVICE_STACK_SIZE  (2048)
#define QMI_DEFAULT_PRIORITY 13;

/*===========================================================================
  FUNCTION  qmi_set_os_params
===========================================================================*/
qmi_task_service_error_type
qmi_set_os_params(task_impl         *task_attr,
          qmi_csi_os_params *os_params)
{
  if (os_params == NULL )
    return QMI_TASK_INVALID_HANDLE;

  os_params->sig = task_attr->sigs;
  os_params->signal = &task_attr->signal;

  return QMI_TASK_SERVICE_NO_ERR;
}

/*===========================================================================
  FUNCTION  qmi_initialize_task
===========================================================================*/
qmi_task_service_error_type
qmi_initialize_task(task_impl    *task_attr,
                    void         *priority,
                    void         *stk_size,
                    void         *sig)
{
    /* Populating with default values */
    if (!sig)
    {
        return QMI_TASK_SERVICE_CREATION_ERR;
    }
    else
    {
        task_attr->sigs = *((unsigned int *)sig);
    }

    if (!stk_size)
    {
        task_attr->stack_size = QMI_SERVICE_STACK_SIZE;
    }
    else
    {
        task_attr->stack_size = *((unsigned int *)stk_size);
    }
        
    if (!priority)
    {
        task_attr->prio = QMI_DEFAULT_PRIORITY;
    }
    else
    {
        task_attr->prio = *((unsigned int *)priority);
    }

    qurt_anysignal_init(&task_attr->signal);
        
    return QMI_TASK_SERVICE_NO_ERR;
}
/*===========================================================================
  FUNCTION  qmi_create_task
===========================================================================*/
qmi_task_service_error_type
qmi_create_task(char          *name,
                task_impl     *task_attr,
                void          *entry_func,
                void          *args)
{

    task_attr->stack_addr = ALLOCATOR(task_attr->stack_size);
    if  ( task_attr->stack_addr == NULL ) {
       return QMI_TASK_SERVICE_MEM_ERR;
    }
    
    qurt_thread_attr_init(&task_attr->thread_attr);
    qurt_thread_attr_set_name(&task_attr->thread_attr, name);
    qurt_thread_attr_set_priority(&task_attr->thread_attr, task_attr->prio);
    qurt_thread_attr_set_stack_size(&task_attr->thread_attr, task_attr->stack_size);
    qurt_thread_attr_set_stack_addr(&task_attr->thread_attr, task_attr->stack_addr);
    qurt_thread_create(&task_attr->thread, &task_attr->thread_attr, 
                        entry_func, args);

     return QMI_TASK_SERVICE_NO_ERR;
}
/*===========================================================================
  FUNCTION  qmi_destroy_task
===========================================================================*/
qmi_task_service_error_type
qmi_destroy_task(task_impl *task_attr)
{
    qurt_anysignal_destroy(&task_attr->signal);
    DEALLOCATE(task_attr->stack_addr);

    return QMI_TASK_SERVICE_NO_ERR;

}


