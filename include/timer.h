#ifndef __JOS_TIMER_H__
#define __JOS_TIMER_H__

#include <ktypes.h>
#include <interrupts.h>
#include <arch.h>
#include <cpu.h>
#include <kernel.h>
#include "../io/kprintf.h"

struct uptime_struct {
    int cseconds;       /* centiseconds. duh */
    int seconds;
    int minutes;
    int hours;
    int days;
};

void init_uptime_struct(struct uptime_struct *);
void uptime_inc_second(struct uptime_struct *);
int get_ticks(void);
void timer_init(uint32_t frequency);

#endif
