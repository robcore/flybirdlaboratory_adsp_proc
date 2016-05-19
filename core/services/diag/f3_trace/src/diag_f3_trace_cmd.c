/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                  F3 Trace DAL Device Configuration Initialization
                
GENERAL DESCRIPTION
  Contains handlers to support F3 message trace retrieval from the EFS.
    
INITIALIZATION AND SEQUENCING REQUIREMENTS
  Should be called after any initialization routines with higher precedence
  (eg post-compilation) such as NV.

Copyright (c) 2012-2013 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*==========================================================================

                        EDIT HISTORY FOR MODULEW
$Header: //components/rel/core.adsp/2.6.1/services/diag/f3_trace/src/diag_f3_trace_cmd.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
11/22/13   sr      Removed PACK from pointer references 
01/25/13   rh      Added ADSP handler 
12/11/12   rh      Initial file creation

===========================================================================*/

#if defined __cplusplus
  extern "C" {
#endif

/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "comdef.h"
#include "msg.h"
#include "diag_f3_tracei.h"
#include "diag_f3_trace_cmd.h"
#include "diagdiag_v.h"
 
/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

===========================================================================*/

void * diag_f3_trace_cmd_handle(void * req_pkt, uint16 pkt_len);

#if defined(DIAG_IMAGE_MODEM_PROC)
static const diagpkt_user_table_entry_type diag_f3_trace_tbl_modem[] = {
  {DIAG_F3_TRACE_SET_CONFIG_MODEM_F, DIAG_F3_TRACE_SET_CONFIG_MODEM_F, diag_f3_trace_cmd_handle}
};
#endif

#if defined(DIAG_F3_TRACE_ADSP_PROC)
static const diagpkt_user_table_entry_type diag_f3_trace_tbl_q6[] = {
  {DIAG_F3_TRACE_SET_CONFIG_Q6, DIAG_F3_TRACE_SET_CONFIG_Q6, diag_f3_trace_cmd_handle}
};
#endif

/*===========================================================================

FUNCTION diag_f3_trace_cmd_reg

DESCRIPTION
  Registers the command to perform runtime configuration of f3 trace

DEPENDENCIES

RETURN VALUE

SIDE EFFECTS

===========================================================================*/
void diag_f3_trace_cmd_reg(void)
{
#if defined(DIAG_IMAGE_MODEM_PROC)
  DIAGPKT_DISPATCH_TABLE_REGISTER_PROC(DIAG_MODEM_PROC, DIAG_SUBSYS_DIAG_SERV, diag_f3_trace_tbl_modem);
#elif defined(DIAG_F3_TRACE_ADSP_PROC)
  DIAGPKT_DISPATCH_TABLE_REGISTER_PROC(DIAG_QDSP6_PROC, DIAG_SUBSYS_DIAG_SERV, diag_f3_trace_tbl_q6);
#endif
}

/*===========================================================================

FUNCTION diag_f3_trace_tbl

DESCRIPTION
  Handles the command to perform runtime configuration of f3 trace

DEPENDENCIES

RETURN VALUE

SIDE EFFECTS

===========================================================================*/
void * diag_f3_trace_cmd_handle(void * req_pkt, uint16 pkt_len)
{
  diag_f3_trace_cmd_hdr_req_type *hdr = (diag_f3_trace_cmd_hdr_req_type *)req_pkt;
  void * rsp_pkt = NULL;
  diagpkt_subsys_cmd_code_type cmd_code = diagpkt_subsys_get_cmd_code (req_pkt);

  if(pkt_len < sizeof(diag_f3_trace_cmd_hdr_req_type)) {
    return diagpkt_err_rsp(DIAG_BAD_LEN_F, req_pkt, pkt_len);
  }

  switch(hdr->cmd) {
  case DIAG_F3_TRACE_CONFIG:
    if(pkt_len < sizeof(diag_f3_trace_config_cmd_type)) {
      rsp_pkt = diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len);
    }
    else {
      diag_f3_trace_config_rsp_type *rsp;
      diag_f3_trace_config_cmd_type *cmd = (diag_f3_trace_config_cmd_type *)req_pkt;
      diag_f3_trace_init_configs(cmd->control, cmd->detail);
      rsp = (diag_f3_trace_config_rsp_type *)diagpkt_subsys_alloc(DIAG_SUBSYS_DIAG_SERV, cmd_code, sizeof(diag_f3_trace_config_rsp_type));
      if (rsp)
        rsp->hdr.cmd = DIAG_F3_TRACE_CONFIG;
      rsp_pkt = rsp;
    }
    break;
  default:
    rsp_pkt = diagpkt_err_rsp(DIAG_BAD_PARM_F, req_pkt, pkt_len);
  }

  return rsp_pkt;
}

#if defined __cplusplus
  }
#endif

