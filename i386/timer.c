#include <timer.h>
#include <kernel.h>

uint32_t ticks = 0;

/* Initialize an uptime struct */
void init_uptime_struct(struct uptime_struct *uptime) {
    uptime->seconds = 0;
    uptime->minutes = 0;
    uptime->hours   = 0;
    uptime->seconds = 0;
    uptime->days = 0;
}

void uptime_inc_second(struct uptime_struct *uptime) {
    uptime->seconds++;
    if(uptime->seconds == 60) {
        uptime->seconds = 0;
        uptime->minutes++;
    }

    if(uptime->minutes == 60) {
        uptime->minutes = 0;
        uptime->hours++;
    }

    if(uptime->hours == 24) {
        uptime->hours = 0;
        uptime->days++;
    }
}

/* The actual timer interrupt function */
static void timer(registers_t t) {
    ++ticks;
    if(ticks % 10 == 0) {
        should_react = 1;
    }
}

/* In theory, this should give a ~1ms timer */
/* This function creates and installs an IDT entry
   for the timer interrupt. It will be called every
   (hopefully) millisecond until "hlt" is called. */
void timer_init(uint32_t frequency) {
    uint32_t div  = 1193180 / frequency;
    uint8_t  low  = (uint8_t)(div & 0xFF);
    uint8_t  high = (uint8_t)((div >> 8) & 0xFF);
    register_interrupt_handler(IRQ0, &timer);

    __asm_outb(0x43, 0x36);
    __asm_outb(0x40, low);
    __asm_outb(0x40, high);
}
