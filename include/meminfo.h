#ifndef __JOS_MM_E820_H__
#define __JOS_MM_E820_H__

#include "../io/kprintf.h"
#include <ktypes.h>

#ifdef i386
#define MAX_ADDR  0xFFFFFFFF
#define E820_LOC  0x2000
#define E820_INFO 0x2400

typedef struct {
    uint32_t base_low;
    uint32_t base_high;
    uint32_t size_low;
    uint32_t size_high;
    uint32_t type;
    uint32_t acpi3_info;
} e820_info;

void get_mem_info();
#endif /* i386 */
#endif
