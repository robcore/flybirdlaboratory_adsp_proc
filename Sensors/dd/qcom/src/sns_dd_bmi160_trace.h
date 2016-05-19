#ifndef __LK_DEBUG_H
#define __LK_DEBUG_H
#include <stdint.h>



#define CONFIG_ENABLE_TP 0

#if CONFIG_ENABLE_TP

#include "fixed_point.h"

#include "qurt_elite_diag.h"
#include "sns_ddf_signal.h"
#include "sns_ddf_attrib.h"
#include "sns_ddf_comm.h"
#include "sns_ddf_common.h"
#include "sns_ddf_driver_if.h"
#include "sns_ddf_memhandler.h"
#include "sns_ddf_signal.h"
#include "sns_ddf_smgr_if.h"
#include "sns_ddf_util.h"
#include "stdbool.h"
#include <string.h>
#include "sns_log_api_public.h"
#include "sns_log_types_public.h"

#define INSERT_TRACE_POINT(mod_tag, tnum) MSG_1(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "trace: %d\n", tnum)
#define INSERT_TRACE_POINT2(mod_tag, tnum1, tnum2) MSG_2(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "trace: %d %d\n", tnum1, tnum2)
#define INSERT_TRACE_POINT3(mod_tag, tnum1, tnum2, tnum3) MSG_3(MSG_SSID_QDSP6, DBG_HIGH_PRIO, "trace: %d %d %d\n", tnum1, tnum2, tnum3);
#else
#define INSERT_TRACE_POINT(mod_tag, tnum)
#define INSERT_TRACE_POINT2(mod_tag, tnum1, tnum2)
#define INSERT_TRACE_POINT3(mod_tag, tnum1, tnum2, tnum3)
#endif

#endif


#define INSERT_TRACE_POINT_T(mod_tag, tnum)
#define INSERT_TRACE_POINT2_T(mod_tag, tnum1, tnum2)
#define INSERT_TRACE_POINT3_T(mod_tag, tnum1, tnum2, tnum3)
#define INSERT_TRACE_POINT4_T(mod_tag, tnum1, tnum2, tnum3, tnum4)

#define INSERT_TRACE_POINT_P(mod_tag, ptr)
