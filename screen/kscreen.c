#include "kscreen.h"

static int _cursorx = 0;
static int _cursory = 0;
static int _cursory_max = 23;
static int _old_cursorx, _old_cursory;

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

void sys_scroll_term() {
    char *pos;
    for(pos = (char *)VMEM + VMEM_LINE_SIZE; pos < (char *)VMEM_LAST_LINE; ++pos) {
        *(pos - VMEM_LINE_SIZE) = *pos;
    }
    for(pos = (char *)VMEM_LAST_LINE - VMEM_LINE_SIZE; pos < (char *)VMEM_LAST_LINE; ++pos) {
        *(pos) = 0;
    }
}

int sys_cursor_overflow(int y) {
    return y == _cursory_max;
}

void sys_init_hw_cursor() {
    __asm_outb(0x3D4, 0x0A);
    __asm_outb(0x3D5, (__asm_inb(0x3D5) & 0xC0) | 0xE);
    __asm_outb(0x3D4, 0x0B);
    __asm_outb(0x3D5, (__asm_inb(0x3E0) & 0xE0) | 0xF);
}

void sys_move_hw_cursor(uint16_t x, uint16_t y) {
    uint16_t pos = y * 80 + x;
    __asm_outb(0x3D4, 0x0F);
    __asm_outb(0x3D5, (uint8_t)(pos & 0xFF));
    __asm_outb(0x3D4, 0x0E);
    __asm_outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void sys_screen_enter_status_mode() {
    _old_cursorx = _cursorx;
    _old_cursory = _cursory;
    _cursory = _cursory_max + 1;
}

void sys_screen_exit_status_mode() {
    _cursorx = _old_cursorx;
    _cursory = _old_cursory;
}
