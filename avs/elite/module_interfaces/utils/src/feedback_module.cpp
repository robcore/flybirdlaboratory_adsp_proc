/*========================================================================
 $Header: //components/rel/avs.adsp/2.6.1/elite/module_interfaces/utils/src/feedback_module.cpp#3 $

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
#include "feedback_module.h"
#include "AFEFeedback.h"
#include "EliteMsg.h"

ADSPResult feedback_push_buf_to_buf_q(void *client_info_ptr, void *pPayLoad)
{
   ADSPResult result = ADSP_EOK;

   if(!pPayLoad || !client_info_ptr)
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Failed NULL ptr payload(%p)! or NULL client info pointer %p", pPayLoad, client_info_ptr);
      return ADSP_EFAILED;
   }

   qurt_elite_queue_t *client_bufQ = ((afe_custom_client_info_t *)client_info_ptr)->bufQ;

   /* send the buffer */
   elite_msg_any_t buf_msg ;
   
   buf_msg.pPayload = pPayLoad;
   buf_msg.unOpCode = 0xFEEDBACC;
   
   result = qurt_elite_queue_push_back(client_bufQ, (uint64_t*)&buf_msg);

   
   return result;
}


ADSPResult feedback_pop_buf_from_data_q(void *client_info_ptr, void **pPayLoad)
{
   ADSPResult result = ADSP_EOK;
   qurt_elite_queue_t *client_dataQ;
   qurt_elite_channel_t *dataQ_chan;
   uint32_t dataQ_chan_bit;
   uint32_t unChannelStatus;
   elite_msg_any_t buf_msg;
   
   if(!(client_info_ptr && pPayLoad))
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Failed NULL ptr client_info_ptr(%p), pPayLoad(%p)!",
            client_info_ptr, pPayLoad);
      return ADSP_EFAILED;
   }

   /* pop the queue  */
   client_dataQ = ((afe_custom_client_info_t *)client_info_ptr)->this_client_manager.dataQ;
   dataQ_chan = qurt_elite_queue_get_channel(client_dataQ);
   dataQ_chan_bit = qurt_elite_queue_get_channel_bit(client_dataQ);

   if((unChannelStatus = qurt_elite_channel_poll(dataQ_chan, dataQ_chan_bit)) != 0)
   {
      /* Pop dataQ until it's empty */
      if(ADSP_FAILED(result = qurt_elite_queue_pop_front(client_dataQ, (uint64_t * )&buf_msg)))
      {
         MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to pop buffer from Queue: 0x%lx", (uint32_t)client_dataQ);
         return result;
      }
      else
      {
        *pPayLoad = buf_msg.pPayload;
      }
      

   } /* End of while loop */

   return result;
}


ADSPResult feedback_pop_buf_from_buf_q(qurt_elite_queue_t *buf_q_ptr, void **payload_pptr)
{
   ADSPResult result = ADSP_EOK;
   qurt_elite_channel_t *bufQ_chan;
   uint32_t unChannelStatus;
   uint32_t bufQ_chan_bit;

   elite_msg_any_t buf_msg;
   
   
   if(!(buf_q_ptr && payload_pptr))
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Failed NULL ptr buf_q_ptr(%p), payload(%p)!",
            buf_q_ptr, payload_pptr);
      return ADSP_EFAILED;
   }

   bufQ_chan = qurt_elite_queue_get_channel(buf_q_ptr);
   bufQ_chan_bit = qurt_elite_queue_get_channel_bit(buf_q_ptr);

   while((unChannelStatus = qurt_elite_channel_poll(bufQ_chan, bufQ_chan_bit)) != 0)
   {
      /* Pop dataQ until it's empty */
      if(ADSP_FAILED(result = qurt_elite_queue_pop_front(buf_q_ptr, (uint64_t * )&buf_msg)))
      {
         MSG_1(MSG_SSID_QDSP6, DBG_ERROR_PRIO, "Failed to pop buffer from Queue: 0x%lx", (uint32_t)buf_q_ptr);
         return result;
      }
      else
      {
        *payload_pptr = buf_msg.pPayload;
      }
      break;
   }

   

   return result;
}


ADSPResult feedback_send_buf_to_data_q(qurt_elite_queue_t *data_q_ptr, void *payload_ptr)
{
   ADSPResult result = ADSP_EOK;
   
   if(!(data_q_ptr && payload_ptr))
   {
      MSG_2(MSG_SSID_QDSP6, DBG_ERROR_PRIO,
            "Failed NULL ptr data_q_ptr(%p), payload(%p)!",
            data_q_ptr, payload_ptr);
      return ADSP_EFAILED;
   }

   elite_msg_any_t buf_msg;

   buf_msg.pPayload = payload_ptr;
   buf_msg.unOpCode = 0xFEEDBACC;
   
   result = qurt_elite_queue_push_back(data_q_ptr,(uint64_t*)&buf_msg);

   return result; 
}

