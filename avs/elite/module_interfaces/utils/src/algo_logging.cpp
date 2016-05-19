/*========================================================================
$Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/utils/src/algo_logging.cpp#3 $

Edit History

when       who     what, where, why
--------   ---     -------------------------------------------------------
7/22/2014   rv       Created

==========================================================================*/

/*-----------------------------------------------------------------------
   Copyright (c) 2012-2015 Qualcomm  Technologies, Inc.  All Rights Reserved.
   Qualcomm Technologies Proprietary and Confidential.
-----------------------------------------------------------------------*/

/*============================================================================
 *                       INCLUDE FILES FOR MODULE
 *==========================================================================*/
#include "algo_logging.h"
#include "algo_logging_i.h"

/**
 * This function is for checking log code status whether it is 
 * enable or not. 
 *
 * @param[in] log_code log code to be checked 
 * @param[out] ADSP_EOK if the code is enabled otherwise 
 *  	 ADSP_EFAILED
 * 
 */
ADSPResult algo_log_status(uint32_t log_code)
{
#ifndef SIM
   if(log_status(log_code))
   {
      return ADSP_EOK;
   }
   return ADSP_EFAILED;
#else
   return ADSP_EOK;
#endif 
}

/**
 * This function is for committing the log buffer
 *
 * @param[in] algo_log_client_info_ptr Ptr to algo log client 
 *  	 info struct
 * 
 */
void algo_log_commit_buf(algo_log_client_info_t* algo_log_client_info_ptr)
{
   if((NULL != algo_log_client_info_ptr->log_buf_ptr) && (algo_log_client_info_ptr->log_size_used))
   {
      elite_log_info log_info_var;
      void *log_pkt_ptr_extn;

      /* Fill the logId with the port ID. */
      log_info_var.buf_ptr                = (uint8_t *)algo_log_client_info_ptr->log_buf_ptr;
      log_info_var.buf_size               = algo_log_client_info_ptr->log_size_used;
      log_info_var.data_fmt               = ELITE_LOG_DATA_FMT_BITSTREAM;
      log_info_var.data_info.media_fmt_id = ELITE_LOG_DATA_FMT_BITSTREAM;
      log_info_var.log_tap_id             = algo_log_client_info_ptr->client_handle;
      log_info_var.log_time_stamp         = qurt_elite_timer_get_time();
      log_info_var.qxdm_log_code          = algo_log_client_info_ptr->log_code;
      log_info_var.session_id             = 0;

      //elite_allocbuf_and_log_data_pkt(&log_info_var);
      if(NULL != (log_pkt_ptr_extn = log_alloc_buffer(algo_log_client_info_ptr->log_size_used, algo_log_client_info_ptr->log_code, ELITE_LOG_DATA_FMT_BITSTREAM)))
      {
        elite_log_buffer(log_pkt_ptr_extn, &log_info_var);
      } 

      algo_log_client_info_ptr->log_size_used = 0;
   }
   return;
}


/**
 * This function is for finding the client info 
 * 
 * @param[in] client_handle_ptr  client handle pointer 
 *
 */
static algo_log_client_info_t* algo_find_client_info(algo_data_logging_t *algo_data_logging_ptr,
                                                     uint32_t client_handle)
{
   client_list_t *client_list_ptr = NULL;
   algo_log_client_info_t* log_info_ptr = NULL;

   client_list_ptr = (client_list_t *)algo_data_logging_ptr->client_list_ptr;

   //find in the client list
   while(client_list_ptr != NULL)
   {
      log_info_ptr = (algo_log_client_info_t *)client_list_ptr->element;
      if(client_handle == log_info_ptr->client_handle)
      {
         return log_info_ptr;
      }
      else
      {
         client_list_ptr = (client_list_ptr->next);
      }
   }

   return NULL;
}


/**
 * This function initializes logging for algo tuning variables
 *
 */
ADSPResult algo_data_logging_init(algo_data_logging_t **algo_data_logging_pptr)
{
   void *mem_ptr = NULL;

   /* Malloc the logging struct */
   mem_ptr = qurt_elite_memory_malloc(sizeof(algo_data_logging_t), QURT_ELITE_HEAP_DEFAULT);
   if(NULL == mem_ptr)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO,"Failed to allocate logging memory!");
      return ADSP_ENOMEMORY;
   }
   *algo_data_logging_pptr = (algo_data_logging_t *)mem_ptr;

   memset(mem_ptr, 0, sizeof(algo_data_logging_t));

   return ADSP_EOK;
}


/**
 * This function deinitializes logging for algo tuning variables
 *
 *
 */
void algo_data_logging_deinit(algo_data_logging_t **algo_data_logging_pptr)
{
   if(!(algo_data_logging_pptr && *algo_data_logging_pptr))
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: Null pointer!");
   }
   else
   {
      if((*algo_data_logging_pptr)->client_counter)
      {
         MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: %u clients not yet deregistered, failed!",
               (*algo_data_logging_pptr)->client_counter);
      }

      qurt_elite_memory_free(*algo_data_logging_pptr);
      *algo_data_logging_pptr = NULL;
   }
}


/**
 * This function is for registering for logging algo tuning variabls
 *
 * @param[in] log_interval_in_ms logging interval in milli sec 
 * @param[in] log_size logging size in bytes
 * @param[in] client_handle_ptr pointer to the client handle
 *  	 pointer
 * @return ADSPResult, retuns success or failure
 *
 */
ADSPResult algo_data_logging_register(algo_data_logging_t *algo_data_logging_ptr,
                                      uint16_t log_interval_in_ms,
                                      uint16_t log_commit_interval_in_ms,
                                      uint32_t log_size,
                                      uint32_t log_code,
                                      uint32_t *client_handle_ptr)
{
   client_list_t          *list_node                = NULL;
   algo_log_client_info_t *algo_log_client_info_ptr = NULL;
   int8_t                 *log_buf_ptr              = NULL;
   client_list_t          **client_list_pptr        = NULL;
   uint32_t               log_size_for_max_algo_interval;

   // return failure if log size is zero
   if(!log_size)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: Non zero logging size need to be provided %ld",
            log_size);
      return ADSP_EUNSUPPORTED;
   }

   // return failure if the log interval size exceeds max log interval
   if(log_interval_in_ms > log_commit_interval_in_ms)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: log interval is greater than the max log interval allowed %d",
            log_interval_in_ms);
      return ADSP_EUNSUPPORTED;
   }

   log_size_for_max_algo_interval = ((log_commit_interval_in_ms / log_interval_in_ms) * log_size);

   // Adding client node
   list_node = (client_list_t *)qurt_elite_memory_malloc((sizeof(client_list_t)), QURT_ELITE_HEAP_DEFAULT);
   if(NULL == list_node)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Out of memory creating client list node.");
      return ADSP_ENOMEMORY;
   }
   //update the client info here
   algo_log_client_info_ptr = (algo_log_client_info_t *)qurt_elite_memory_malloc(
         sizeof(algo_log_client_info_t), QURT_ELITE_HEAP_DEFAULT);
   if(NULL == algo_log_client_info_ptr)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Out of memory creating afe algo client list node.");
      qurt_elite_memory_free(list_node);
      return ADSP_ENOMEMORY;
   }

   list_node->element = (void*)algo_log_client_info_ptr;
   list_node->next = NULL;

   memset(algo_log_client_info_ptr, 0, sizeof(algo_log_client_info_t));

   log_buf_ptr = (int8_t *)qurt_elite_memory_malloc(log_size_for_max_algo_interval, QURT_ELITE_HEAP_DEFAULT);
   if(NULL == log_buf_ptr)
   {
      MSG(MSG_SSID_QDSP6, DBG_ERROR_PRIO, " Error allocating memory for algo log buffer");
      qurt_elite_memory_free(list_node);
      qurt_elite_memory_free(algo_log_client_info_ptr);
      return ADSP_ENOMEMORY;
   }

   algo_log_client_info_ptr->client_handle      = (uint32_t)algo_log_client_info_ptr;
   algo_log_client_info_ptr->log_buf_ptr        = log_buf_ptr;
   algo_log_client_info_ptr->log_buf_size       = log_size_for_max_algo_interval;
   algo_log_client_info_ptr->log_interval_in_ms = log_interval_in_ms;
   algo_log_client_info_ptr->log_size           = log_size;
   algo_log_client_info_ptr->log_size_used      = 0;
   algo_log_client_info_ptr->log_code           = (elite_qxdm_log_code)log_code;

   client_list_pptr = (client_list_t **)&algo_data_logging_ptr->client_list_ptr;

   // Adding the client to the front
   if(*client_list_pptr)
   {
      list_node->next = *client_list_pptr;
   }
   *client_list_pptr = list_node;

   *client_handle_ptr = algo_log_client_info_ptr->client_handle;
   algo_data_logging_ptr->client_counter++;

   return ADSP_EOK;
}


/**
 * This function is for deregistering the client for logging algo tuning
 * variable
 *
 * @param[in] client_handle_ptr client handle pointer 
 * @return ADSPResult, retuns success or failure
 *
 */
ADSPResult algo_data_logging_deregister(algo_data_logging_t *algo_data_logging_ptr,
                                        uint32_t client_handle)
{
   client_list_t          *cur_client_list_ptr  = NULL;
   client_list_t          *prev_client_list_ptr = NULL;
   algo_log_client_info_t *log_info_ptr         = NULL;
   bool_t                 is_dereg_done         = FALSE;

   cur_client_list_ptr = (client_list_t *)algo_data_logging_ptr->client_list_ptr;
   if(NULL == cur_client_list_ptr)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: client list ptr is NULL, failed to dereg client :0x%lx",
            client_handle);
      return ADSP_EFAILED;
   }

   //find the client and remove the same
   while(cur_client_list_ptr)
   {
      log_info_ptr = (algo_log_client_info_t *)cur_client_list_ptr->element;

      if(log_info_ptr->client_handle == client_handle)
      {
         if(NULL == prev_client_list_ptr) // If first node is removed
         {
            algo_data_logging_ptr->client_list_ptr = cur_client_list_ptr->next;
         }
         else
         {
            prev_client_list_ptr->next = cur_client_list_ptr->next;
         }

         // commit the existing log buffer
         algo_log_commit_buf(log_info_ptr);
         qurt_elite_memory_free(log_info_ptr->log_buf_ptr);
         qurt_elite_memory_free(log_info_ptr);
         qurt_elite_memory_free(cur_client_list_ptr);
         is_dereg_done = TRUE;
         break;
      }

      prev_client_list_ptr = cur_client_list_ptr;
      cur_client_list_ptr = cur_client_list_ptr->next;
   }

   if(!is_dereg_done)
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: failed to dereg client :0x%lx, not in client list",
            client_handle);
      return ADSP_EFAILED;
   }

   algo_data_logging_ptr->client_counter--;
   return ADSP_EOK;
}


/**
 * This function does the logging for algo tuning variables
 *
 * @param[in] log_buffer Ptr to the buffer to be logged. 
 * @param[in] log_size logging size in bytes 
 * @param[in] client_handle_ptr client handle pointer 
 *  
 */
ADSPResult algo_data_log_now(algo_data_logging_t *algo_data_logging_ptr,
                             int8_t *log_buffer,
                             uint32_t log_size,
                             uint32_t client_handle)
{
   uint32_t log_buf_size;
   uint32_t log_size_used = 0;
   int8_t *log_buf_ptr = NULL;

   algo_log_client_info_t *algo_log_client_info_ptr = NULL;

   if(NULL == (algo_log_client_info_ptr = algo_find_client_info(algo_data_logging_ptr, client_handle)))
   {
      MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Algo Log: algo client is not found 0x%lx", client_handle);
      return ADSP_EFAILED;
   }

   /* Validate the log size */
   if(log_size != algo_log_client_info_ptr->log_size)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Algo Log: log size registered %ld is different from log size %ld being logged",
            algo_log_client_info_ptr->log_size, log_size);
      return ADSP_EFAILED;
   }

   if(NULL != algo_log_client_info_ptr->log_buf_ptr)
   {
      log_buf_size  = algo_log_client_info_ptr->log_buf_size;
      log_size_used = algo_log_client_info_ptr->log_size_used;
      log_buf_ptr   = algo_log_client_info_ptr->log_buf_ptr;

      if((log_size_used + log_size) <= log_buf_size)
      {
         //dest buffer will have the free space of  (log_buf_size-log_size_used)
         memscpy(log_buf_ptr + (log_size_used), (log_buf_size - log_size_used), log_buffer,
               log_size);

         /* Update used log buffer size */
         algo_log_client_info_ptr->log_size_used += log_size;

         /* If all the log buffer size has been used, do commit the log buffer. */
         if(algo_log_client_info_ptr->log_size_used >= (log_buf_size))
         {
            algo_log_commit_buf(algo_log_client_info_ptr);
         }
      }
      else
      {
         algo_log_commit_buf(algo_log_client_info_ptr);
         //dest buffer will have the free space of  (log_buf_size-log_size_used)

         /* algo_log_client_info_ptr->log_size_used is reset to 0 inside commit func */
         memscpy(log_buf_ptr, log_buf_size, log_buffer, log_size);

         /* Update used log buffer size */
         algo_log_client_info_ptr->log_size_used += log_size;
      }
   }

   return ADSP_EOK;
}
