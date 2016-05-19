#ifndef ELITE_FWK_EXTNS_FEEDBACK_SPKR_PROT_H
#define ELITE_FWK_EXTNS_FEEDBACK_SPKR_PROT_H

/* ======================================================================== */
/**
@file Elite_fwk_extns_feedback_spkr_prot.h

@brief frame work extensions for feedback speaker protection header file

  This file defines a framework extensions and corresponding private propeties
  needed for feedback speaker protection.
*/

/*===========================================================================
NOTE: The @brief description above does not appear in the PDF.

      The Elite_APPI_mainpage.dox file contains the group/module descriptions that
      are displayed in the output PDF generated using Doxygen and LaTeX. To
      edit or update any of the group/module text in the PDF, edit the
      Elite_APPI_mainpage.dox file or contact Tech Pubs.
===========================================================================*/

/* =========================================================================
  Copyright (c) 2010-2014 Qualcomm Technologies, Inc.(QTI)
  All rights reserved. Qualcomm Proprietary and Confidential.
  ========================================================================== */

/* =========================================================================
                             Edit History

   when       who     what, where, why
   --------   ---     ------------------------------------------------------
   05/16/14   mk      Initial Version.
   ========================================================================= */

#include "Elite_CAPI_V2_types.h"

#define FWK_EXTN_FEEDBACK_SPKR_PROT 0x00010906
/**< Unique identifier to represent custom framework extension for feedback speaker protection */


#define APPI_PARAM_ID_CLIENT_INFO 0x000108FF
/**< Unique identifier to send the custom client information to the algorithm appi framework to use it for passing custom data between two appi modules on different threads. 
  For example:

  CALLER
      appi_buf_t params_buf;
      params_buf.data_ptr = (int8_t*)cust_client_list_ptr;
      params_buf.actual_data_len = sizeof(bufQList*);
      params_buf.max_data_len = sizeof(bufQList*);
      (void)appi_ptr->vtbl_ptr->set_param (
         so.appi_ptr, 
         APPI_PARAM_ID_CLIENT_INFO, 
         &params_buf);

  CALLEE
      // Read data_ptr and max_data_len 
	 // Read and Cache the cust_client_list_ptr for future use
 
	Refer to /adsp_proc/avs/afe/services/static/inc/AFEInternal.h for the definition of bufQList
 */


#define APPI_PARAM_ID_BGT_INFO 0x00010900
/**< Unique identifier to send the back ground thread handler information to the algorithm appi framework for the use of instantiating background thread for algorithm processing. 
  Content is associated with appi_bgt_info_t structure
  For example:

  CALLER
      appi_buf_t params_buf;
      appi_bgt_info_t bgt_info;
      afe_dev_port_t *pDevPort;
 
	  bgt_info.intf = pDevPort->intf;
	  bgt_info.bgt_handle = &pDevPort->bgt_handle;
	
      params_buf.data_ptr = (int8_t*)&bgt_info;
      params_buf.actual_data_len = sizeof(appi_bgt_info_t);
      params_buf.max_data_len = sizeof(appi_bgt_info_t);
      (void)appi_ptr->vtbl_ptr->set_param (
         so.appi_ptr, 
         APPI_PARAM_ID_BGT_INFO, 
         &params_buf);

  CALLEE
      // Read data_ptr and max_data_len
	  while (payload_size)
      {
		  // Cache the bgt handle information for future use

      };
 
	  Refer to /adsp_proc/avs/afe/services/static/inc/AFEInternal.h for the definition of afe_dev_port_t
 */

/** @ingroup data_types
  Structure for a back ground thread information that is passed
  into APPI functions. 
   
  This background information is used by APPI modules to use 
  self destructing background thread. 
 */
typedef struct appi_bgt_info_t
{
	int16_t             intf;
						/**< AFE port interface which contains the back ground thread handler */
	void				**bgt_handle;
						/**< pointer to background thread handler */

}appi_bgt_info_t;

#define APPI_PARAM_ID_FB_PATH_INFO 0x00010901
/**< Unique identifier to send the feedback path information to the algorithm appi framework for the use of feedback path between two appi modules on different threads
  For example:

  CALLER
      appi_buf_t params_buf;
      
      params_buf.data_ptr = (int8_t*)&feedback_path_info;
      params_buf.actual_data_len = sizeof(afe_port_feedback_info_t);
      params_buf.max_data_len = sizeof(afe_port_feedback_info_t);
      (void)appi_ptr->vtbl_ptr->set_param (
         so.appi_ptr, 
         APPI_PARAM_ID_FB_PATH_INFO, 
         &params_buf);

  CALLEE
      // Read data_ptr and max_data_len
  	  while (payload_size)
      {
		  // Cache the feedback path information for future use

      };
	  Refer to /adsp_proc/avs/afe/services/static/inc/AFEFeedback.h for the definition of afe_port_feedback_info_t
 */

#define APPI_PARAM_ID_INT_INFO 0x00010902
/**< Unique identifier to send the Interrrupt information to the appi framework
  For example:

  CALLER
      appi_buf_t params_buf;
      
      params_buf.data_ptr = (int8_t*)&int_info;
      params_buf.actual_data_len = sizeof(interrupt data type);
      params_buf.max_data_len = sizeof(interrupt data type);
      (void)appi_ptr->vtbl_ptr->set_param (
         so.appi_ptr, 
         APPI_PARAM_ID_INT_INFO, 
         &params_buf);

  CALLEE
      // Read data_ptr and max_data_len 
      // Read and Pass the interrupt information to algorithm
 */

#define APPI_PARAM_ID_CLIP_PCM_INFO 0x00010903
/**< Unique identifier to send the clip pcm levels information to the appi algo framework to handle pcm levels when clip interrupt occurs (specific to feedback speaker protection)
  For example:

  CALLER
      appi_buf_t params_buf;
      
      params_buf.data_ptr = (int8_t*)&int_info;
      params_buf.actual_data_len = sizeof(uint8_t) * number of pcm levels;
      params_buf.max_data_len = sizeof(uint8_t) * number of pcm levels;
      (void)appi_ptr->vtbl_ptr->set_param (
         so.appi_ptr, 
         APPI_PARAM_ID_CLIP_PCM_INFO, 
         &params_buf);

  CALLEE
      // Read data_ptr and max_data_len
	  while (payload_size)
      {
          //read the pcm levels from param_buffer_ptr and pass to algorithm library process
      };
 */

#endif /* #ifndef ELITE_FWK_EXTNS_FEEDBACK_SPKR_PROT_H */
