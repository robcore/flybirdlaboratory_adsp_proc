#ifndef UIMAGE_RPM_ASSERT_H
#define UIMAGE_RPM_ASSERT_H

#include "uimage_rpm_log.h"
#include "CoreVerify.h"

#define UIMAGE_RPM_ASSERT(cond, err_msg)                                                \
    do {                                                                                \
        if(!(cond)) {                                                                   \
            if(err_msg != NULL)                                                         \
                UIMAGE_RPM_LOG(3, "Error @ %d in %s: %s", __LINE__, __func__, err_msg); \
            CORE_VERIFY(0);                                                             \
        }                                                                               \
    } while(0)

#endif /* UIMAGE_RPM_ASSERT_H */

