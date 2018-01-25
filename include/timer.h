#ifndef __JOS_TIMER_H__
#define __JOS_TIMER_H__

#include <ktypes.h>
#include <interrupts.h>
#include <arch.h>
#include <cpu.h>
#include "../io/kprintf.h"

int get_ticks(void);
void timer_init(uint32_t frequency);

#endif
