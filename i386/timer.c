#include <timer.h>
#include <kernel.h>

uint32_t ticks = 0;

int get_ticks(void) {
    return ticks;
}

static void timer(registers_t t) {
    ++ticks;
    kprintf("tick!\n");
}

void timer_init(uint32_t frequency) {
    uint32_t div  = 1193180 / frequency;
    uint8_t  low  = (uint8_t)(div & 0xFF);
    uint8_t  high = (uint8_t)((div >> 8) & 0xFF);
    register_interrupt_handler(IRQ0, &timer);

    __asm_outb(0x43, 0x36);
    __asm_outb(0x40, low);
    __asm_outb(0x40, high);
}
