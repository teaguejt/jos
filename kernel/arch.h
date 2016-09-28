#ifndef __JOS_ARCH_H__
#define __JOS_ARCH_H__

#include "ktypes.h"

struct registers {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esp;
};

void __asm_getreg(struct registers *);
void __asm_outb(uint16_t port, uint8_t value);
void __asm_outw(uint16_t port, uint16_t value);
void __asm_outd(uint16_t port, uint32_t value);
inline uint8_t __asm_inb(uint16_t port);
inline uint16_t __asm_inw(uint16_t port);
inline uint32_t __asm_ind(uint16_t port);

#endif
