#ifndef SNS_OCMEM_H
#define SNS_OCMEM_H

/*============================================================================

  @file sns_ocmem.h

  @brief
  This file contains declarations for common sensors ocmem code.

            Copyright (c) 2012 Qualcomm Technologies Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

============================================================================*/

#include <stdint.h>

/*============================================================================
                        Type Declarations
=============================================================================*/

typedef enum {
  SNS_OCMEM_MODULE_KERNEL = 0,
  SNS_OCMEM_MODULE_ADSP
} sns_ocmem_module_e;

typedef enum {
  SNS_OCMEM_SUCCESS = 0,
} sns_ocmem_error_e;

/**
 * Defines the types of response messages
 */
typedef enum {
  SNS_OCMEM_MSG_TYPE_REQ = 0,  /* Request */
  SNS_OCMEM_MSG_TYPE_RESP,     /* Response to a request */
  SNS_OCMEM_MSG_TYPE_IND       /* Asynchronous indication */
} sns_ocmem_msg_type_e;

/**
 * The message header. Used in both incoming and outgoing messages
 */


typedef struct
{
  int32_t  msg_id ;      /* Message ID, as defined in the IDL */
  uint16_t msg_size;    /* Size, in bytes, of the c-structure representing the message */  
  uint8_t  dst_module;  /* Destination module */
  uint8_t  src_module ;  /* Source module */
  uint8_t  msg_type;    /* The message type */
} __attribute__((packed,aligned (1))) sns_ocmem_hdr_s;


void* sns_ocmem_main( void* );

#endif /* SNS_OCMEM_H */
