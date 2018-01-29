#include "keyboard.h"

static void keyboard(registers_t t) {
    char c = 0;

    kprintf("keyboard event: ");
    do {
        if(__asm_inb(0x60) != c) {
            c = __asm_inb(0x60);
            if(c > 0) {
                kprintf("0x%x\n", (int)c);
                break;
            }
        }
    } while(1);
}

void keyboard_init() {
    register_interrupt_handler(IRQ1, &keyboard);
}
