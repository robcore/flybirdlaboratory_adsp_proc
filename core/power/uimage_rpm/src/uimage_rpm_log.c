#include "uimage_rpm_log.h"
#include "uimage_rpm_assert.h"

#define UIMAGE_RPM_LOG_NAME     "uimage_rpm_master_log" /* max 23 chars + null */
#define UIMAGE_RPM_LOG_SIZE     MICRO_ULOG_MEM_NEEDED(1024)


/* a handle to the uImage RPM micro_ULog */
micro_ULogHandle uImage_rpm_log_hnd = NULL;

/* Pre-allocated log buffers required for island mode */
static char uImage_rpm_log_buffer[UIMAGE_RPM_LOG_SIZE];


/*******************************************************************************
 *
 * uImage_rpm_log_init
 *
 * This function is used to initialize log handler for uImage RPM.
 *
 */
void uImage_rpm_log_init(void)
{
    uint32            effective_buf_size;
    micro_ULogResult  status;

    status = micro_ULog_CreateLog(&uImage_rpm_log_hnd,
                                  UIMAGE_RPM_LOG_NAME,
                                  uImage_rpm_log_buffer,
                                  &effective_buf_size,
                                  sizeof(uImage_rpm_log_buffer));

    UIMAGE_RPM_ASSERT(MICRO_ULOG_SUCCESS == status, NULL /* cannot log */);

    /* Enabling the log */
    micro_ULog_Enable(uImage_rpm_log_hnd);

    UIMAGE_RPM_LOG(0, "log_init_done", NULL);
}

