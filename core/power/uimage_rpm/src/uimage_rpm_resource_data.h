#ifndef UIMAGE_RPM_RESOURCE_DATA_H
#define UIMAGE_RPM_RESOURCE_DATA_H

#include "DALStdDef.h"

typedef struct
{
    const uint32 resource_type;
    const uint32 resource_id;
    const uint32 resource_key;
    uint32 resource_value;
} uImage_rpm_resource_info_t;

typedef struct
{
    uImage_rpm_resource_info_t * const resources;
    uint32 num_resources;
} uImage_rpm_resource_info_array_t;

extern uImage_rpm_resource_info_array_t uImage_rpm_ddr_resource_data;

#endif /* UIMAGE_RPM_RESOURCE_DATA_H */

