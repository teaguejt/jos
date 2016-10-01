#ifndef __JOS_CPU_H__
#define __JOS_CPU_H__

#include "ktypes.h"

struct cpu_info {
    uint32_t max_capabilities;
    char brand_string[48];
    char vendor_string[13];
};

void get_cpu_data(struct cpu_info *);

#endif
