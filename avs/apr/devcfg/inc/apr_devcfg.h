#include "mmdefs.h"

#ifndef APR_DEVCFG_H
#define APR_DEVCFG_H

typedef enum {
  apr_smdl,
  apr_smd,
  apr_hsuart
} apr_devcfg_ipc_enum_t;

typedef struct  {
    uint32_t              smdl_buffer_size;
    apr_devcfg_ipc_enum_t ipc_technology_enum;
} apr_devcfg_prop_struct_t;

#endif // APR_DEVCFG_H
