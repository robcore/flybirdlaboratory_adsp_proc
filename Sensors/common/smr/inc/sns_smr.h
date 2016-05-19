#ifndef SNS_SMR_H
#define SNS_SMR_H

/*============================================================================

  @file sns_smr.h

  @brief
  This file contains definition for SMR(Sensor Message Router)

  Copyright (c) 2010-2012 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.

============================================================================*/


/*============================================================================

                        EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/ssc.adsp/2.6.1/common/smr/inc/sns_smr.h#1 $


when         who     what, where, why
----------   ---     ---------------------------------------------------------
2012-12-07   gju     Provide get_hdr and set_hdr for all platforms
2012-10-02   ag      Allow compatibility with SMR and QMI targets
2012-09-13   vh      Changed the size of svc_num in sns_smr_header_s from uint8_t to uint16_t
2012-08-09   ag      Updated to use official QMI service IDs
2011-11-14   jhh     Modified API for alloc and free
2010-10-24   br      Inserted a macro SNS_SMR_IS_INTERNAL_MODULE
2010-04-15   br      Deleted obsolete API: sns_smr_q_register()
2010-10-27   br      Adjusted SMR_MAX_BODY_LEN according to log packet message size
2010-10-20   br      Defined SMR_MAX_BODY_LEN, and inserted a prototype:sns_smr_get_qmi_max_encode_msg_len
2010-08-30   JTL     Moving init function decl into sns_init.h
2010-07-25   br      Change structures such as sns_smr_header_s, and cleaned-up comments
2010-06-28   br      A few comments were updated
2010-06-20   br      Initial Release

============================================================================*/


/*===========================================================================

                   EXTERNAL DEFINITIONS AND TYPES

===========================================================================*/
#include  "sns_queue.h"
#include  "sns_common.h"
#include  "sensor1.h"
#include  "qmi_idl_lib.h"
#include  "comdef.h" /* For PACK */
#include  "sns_debug_api.h"


/*============================================================================

                Preprocessor Definitions and Constants

============================================================================*/
#define SMR_MAX_BODY_LEN  850   /* The max body length to be allocated by sns_smr_msg_alloc() */

/*============================================================================

                Macro definition

============================================================================*/
#define SNS_SMR_IS_INTERNAL_MODULE(module) ((((module)&SNS_MODULE_GRP_MASK)==SNS_THIS_MODULE_GRP)?true:false)

/*============================================================================

                        Type Declarations

=============================================================================*/
typedef enum {
  SNS_SMR_MSG_TYPE_REQ = SENSOR1_MSG_TYPE_REQ,
  SNS_SMR_MSG_TYPE_RESP = SENSOR1_MSG_TYPE_RESP,
  SNS_SMR_MSG_TYPE_IND = SENSOR1_MSG_TYPE_IND,
  SNS_SMR_MSG_TYPE_RESP_INT_ERR = SENSOR1_MSG_TYPE_RESP_INT_ERR,
  SNS_SMR_MSG_TYPE_LAST,
} sns_smr_msg_type_e;

typedef enum {
  SNS_SMR_MSG_PRI_LOW = 0,
  SNS_SMR_MSG_PRI_HIGH,
  SNS_SMR_MSG_PRI_LAST
} sns_smr_msg_pri_e;

typedef PACK(struct)
{
  uint8_t  dst_module;       /* Destination module ID within the Sensors framework */
  uint8_t  src_module;       /* Source module ID within the Sensors framework */
  uint8_t  priority;         /* The message priority */
  uint8_t  txn_id;           /* SMR client provided transaction ID */
  uint8_t  ext_clnt_id;      /* External client ID provided by a SMR client */
  uint8_t  msg_type;         /* The message type- refer sns_smr_msg_type_e */
  uint8_t  for_align0;       /* For alignment */
  uint8_t  svc_num;          /* The service number defined in the QMI header file */
  uint16_t msg_id;           /* The message identifier */
  uint16_t body_len;         /* The body length. i.e. header length is excluded */
#ifdef SNS_QMI_ENABLE
  void*    connection_handle;
  qmi_req_handle req_handle;
#endif
 } sns_smr_header_s;

 #ifndef SNS_QMI_ENABLE
/*============================================================================

                        External Variable Declarations

============================================================================*/
/*
 * Each module shall sem_post to this semaphore after module initialization
 * is complete.
 */
extern OS_EVENT *sns_init_sem_ptr;

/*===========================================================================

  FUNCTION:   sns_smr_register

===========================================================================*/
/*!
  @brief This function registers an event handle which will be used to signal to the module
         when a message is arrived.

  @param[i] module_id: The sensor module id which is unique within the sensor framework.
  @param[i] sig_grp_ptr: A pointer to the signal group to which sig_flag is associated
  @param[i] sig_flag: The signal flag that triggers the event

  @return
   - SNS_SUCCESS if the message queues was registered successfully.
   - All other values indicate an error has occurred.

*/
/*=========================================================================*/
sns_err_code_e sns_smr_register(uint8_t module_id, OS_FLAG_GRP *sig_grp_ptr, OS_FLAGS sig_flag);

/*===========================================================================

  FUNCTION:   sns_smr_send

===========================================================================*/
/*!
  @brief This function transfers the message to an appropriate module within the Sensors framework
   
  @param[i] body_ptr: A pointer to the message body allocated by sns_smr_msg_alloc

  @return
   - SNS_SUCCESS if the message header was gotten successfully.
   - SNS_ERR_WOULDBLOCK if some resource is tentatively unavailable.
   - All other values indicate an error has occurred.

*/
/*=========================================================================*/
sns_err_code_e sns_smr_send(void* body_ptr);

/*===========================================================================

  FUNCTION:   sns_smr_rcv

===========================================================================*/
/*!
  @brief returns a message body from one of the module’s queues 
   
  @param[i] module_id: The module ID that calls this function.

  @return
   NULL if there was no more message in the queues, or a pointer to the message body

*/
/*=========================================================================*/
void* sns_smr_rcv(uint8_t module_id);

/*===========================================================================

  FUNCTION:   sns_smr_get_qmi_max_encode_msg_len

===========================================================================*/
/*!
  @brief This function returns the maximum encoded message length for all services
         which are used in this framework.
   
  @return
   the maximum encoded message length 

*/
/*=========================================================================*/
uint16_t  sns_smr_get_qmi_max_encode_msg_len (void);

/*===========================================================================

  FUNCTION:   sns_smr_close

===========================================================================*/
/*!
  @brief  Close the SMD port
   
  @param[i] None

  @detail
  
  @return
   - SNS_SUCCESS if close system call was success.
   - SNS_ERR_FAILED if an error occurred.

*/
/*=========================================================================*/
sns_err_code_e sns_smr_close (void);
#endif /* SNS_QMI_ENABLE */

/*===========================================================================

  FUNCTION:   sns_smr_set_hdr

===========================================================================*/
/*!
  @brief This function sets message header information with the parameters delivered using
         sns_smr_header_s structure type.
         The address of the message header is calculated from body_ptr.
   
  @param[i] header_type_ptr: A pointer to the header structure type variable which includes all parameters.
            The message header is identified by body_ptr.
  @param[i] body_ptr: A pointer to the message body allocated by sns_smr_msg_alloc

  @return
   - SNS_SUCCESS if the message header was set successfully.
   - All other values indicate an error has occurred.

*/
/*=========================================================================*/
sns_err_code_e sns_smr_set_hdr(const sns_smr_header_s * header_type_ptr, void * body_ptr);

/*===========================================================================

  FUNCTION:   sns_smr_get_hdr

===========================================================================*/
/*!
  @brief This function gets message header information into sns_smr_header_s structure type.
   
  @param[o] header_type_ptr: A pointer to the header structure type in which
            the header informaiton will be retrieved
  @param[i] body_ptr: A pointer to the message body allocated by sns_smr_msg_alloc

  @return
   - SNS_SUCCESS if the message header was gotten successfully.
   - All other values indicate an error has occurred.
*/
/*=========================================================================*/
sns_err_code_e sns_smr_get_hdr(sns_smr_header_s * header_type_ptr, const void * body_ptr);

/*===========================================================================

  FUNCTION:   sns_smr_msg_alloc

===========================================================================*/
/*!
  @brief this function allocates message body and header and returns the body pointer.

  @param[i] body_size is the message body size to be allocated

  @return
  NULL if failed, or a pointer to the newly allocated message body

*/
/*=========================================================================*/
void * sns_smr_msg_alloc(sns_debug_module_id_e src_module, uint16_t body_size);

/*===========================================================================

  FUNCTION:   sns_smr_msg_free

===========================================================================*/
/*!
  @brief This function frees the message header and body allocated by sns_smr_msg_alloc().

  @param[i] body_ptr: A pointer variable to the message body to be freed

  @return
   None

*/
/*=========================================================================*/
void sns_smr_msg_free(void * body_ptr);

/*===========================================================================

  FUNCTION:   sns_smr_get_svc_obj

===========================================================================*/
/*!
  @brief This function returns a service object by using the routing table.
   
  @param[i] svc_num: The service number which determines the service object

  @return
   The service object or NULL if the svc_num is not defined 

*/
/*=========================================================================*/
qmi_idl_service_object_type  sns_smr_get_svc_obj (uint8_t svc_num);

/*===========================================================================

  FUNCTION:  smr_set_qmi_service_obj

===========================================================================*/
/**
  @brief set service object into the routing table

  @detail

  @return None

*/
/*=========================================================================*/
void smr_set_qmi_service_obj (void);

#ifdef SNS_QMI_ENABLE
/*===========================================================================

  FUNCTION:   sns_smr_get_rtb_size

===========================================================================*/
/*!
  @brief This function returns the size of the routing table.

  @param[i] 

  @return
   The macro SNS_SMR_RTB_SIZE is available only in this C file. Hence a function
   is needed to access this by other external modules.

*/
/*=========================================================================*/
uint8_t  sns_smr_get_rtb_size (void);


/*===========================================================================

  FUNCTION:   sns_smr_get_module_id

===========================================================================*/
/*!
  @brief This function returns the module_id from the routing table.

  @param[i] svc_num: The service number which determines the module id

  @return
   0xFF if svc_num is invalid

*/
/*=========================================================================*/
uint8_t  sns_smr_get_module_id (uint8_t svc_num);
#endif /* SNS_QMI_ENABLE */
#endif /* SNS_SMR_H */
