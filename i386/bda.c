/* Support functions for managing the BDA.
   Okay, support FUNCTION.
   If you want to know why this is doing what it does, find the oldest
   IBM PC Jr. manual you can, and read it. */

#include <bda.h>
#include "../io/kprintf.h"

bda_info_t __bda_info;

void populate_bda_struct() {
    int i;
    uint16_t *ptr = (uint16_t *)BDA_BEGIN;

    for(i = 0; i < BDA_MAX_COMS; i++)
        __bda_info.com_ports[i] = *ptr++;

    for(i = 0; i < BDA_MAX_LPTS; i++)
        __bda_info.lpt_ports[i] = *ptr++;

    ptr = (uint16_t *)BDA_DISP_COLS;
    __bda_info.display_cols = *ptr;

    ptr = (uint16_t *)BDA_DISP_PORT;
    __bda_info.vid_port = *ptr;
}

void display_bda_info() {
    uint8_t mode = 0x74;
    int i;
    
    kcprintf(mode, "BIOS Data Area Information\n");

    for(i = 0; i < BDA_MAX_COMS; i++) {
        if(__bda_info.com_ports[i] == 0)
            continue;
        kprintf("   COM%d: 0x%x\n", i + 1, __bda_info.com_ports[i]);
    }

    for(i = 0; i < BDA_MAX_LPTS; i++) {
        if(__bda_info.lpt_ports[i] == 0)
            continue;
        kprintf("   LPT%d: 0x%x\n", i + 1, __bda_info.lpt_ports[i]);
    }

    kprintf("   Display Port: 0x%lx\n", __bda_info.vid_port);
    kprintf("   Display Cols: %d\n", __bda_info.display_cols);
    kprintf("\n");
}
