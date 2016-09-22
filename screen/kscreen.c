#include "kscreen.h"

static int _cursorx = 0;
static int _cursory = 5;

void sys_clear_screen() {    
    char *vmem = (char *)VMEM;
    char spc = ' ';
    char col = 0x0F;

    while( vmem < (char *)VMEM_END ) {
        *vmem++ = spc;
        *vmem++ = col;
    }

    _cursorx = 0;
    _cursory = 0;
}

void sys_set_cursorx( int n ) {
    _cursorx = n;
}

void sys_set_cursory( int n ) {
    _cursory = n;
}

int sys_get_cursorx() {
    return _cursorx;
}

int sys_get_cursory() {
    return _cursory;
}

int *sys_get_cursorx_addr() {
    return &_cursorx;
}

int *sys_get_cursory_addr() {
    return &_cursory;
}
