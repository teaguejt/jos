#include "arch.h"
#include "cpu.h"

void get_cpu_data(struct cpu_info *info) {
    info->max_capabilities = __asm_getcpumaxid();
    __asm_getcpustring(info->vendor_string);
    
    /* Get the full brand string, if supported */
    if(info->max_capabilities >= 0x80000004) {
        __asm_getcpubrandstring(info->brand_string);
    }
}
