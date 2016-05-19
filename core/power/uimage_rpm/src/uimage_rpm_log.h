#ifndef UIMAGE_RPM_LOG_H
#define UIMAGE_RPM_LOG_H

#include <stdarg.h>
#include "DALStdDef.h"
#include "micro_ULog.h"

#define UIMAGE_RPM_LOG(num_args, fmt, ...) \
    micro_ULog_RealTimePrintf(uImage_rpm_log_hnd, num_args, fmt, __VA_ARGS__) 


extern micro_ULogHandle uImage_rpm_log_hnd;

/*******************************************************************************
 *
 * uImage_rpm_log_init
 *
 * This function is used to initialize log handler for uImage RPM.
 *
 */
void uImage_rpm_log_init(void);

#endif /* UIMAGE_RPM_LOG_H */
