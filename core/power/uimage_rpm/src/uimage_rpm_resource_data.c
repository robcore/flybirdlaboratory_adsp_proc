#include "uimage_rpm_resource_data.h"
#include "rpm.h"

#define UIMAGE_SNOC_RESOURCE_KEY 0x007a484b /* "KHz" */
#define UIMAGE_BMIC_RESOURCE_KEY 0x007a484b /* "KHz" */


static uImage_rpm_resource_info_t uImage_rpm_ddr_resources[] =
{
    {
        /*
         * SNOC bus clock
         */
        .resource_type = RPM_CLOCK_1_REQ,
        .resource_id   = 1,
        .resource_key  = UIMAGE_SNOC_RESOURCE_KEY,
    },
    {
        /*
         * BIMC clock
         */
        .resource_type = RPM_CLOCK_2_REQ,
        .resource_id   = 0,
        .resource_key  = UIMAGE_BMIC_RESOURCE_KEY,
    },
};

uImage_rpm_resource_info_array_t uImage_rpm_ddr_resource_data =
{
    .resources     = uImage_rpm_ddr_resources,
    .num_resources = sizeof(uImage_rpm_ddr_resources) / sizeof(uImage_rpm_ddr_resources[0]),
};

