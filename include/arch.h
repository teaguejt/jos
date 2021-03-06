#ifndef __JOS_ARCH_H__
#define __JOS_ARCH_H__

#include <ktypes.h>

struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp;
    uint32_t ebx, edx, ecx, eax;
    uint32_t interrupt, err;
    uint32_t eip, cs, flags, uesp, ss;
};

void __asm_getreg(struct registers *);

/* Port input and output */
void __asm_outb(uint16_t port, uint8_t value);
void __asm_outw(uint16_t port, uint16_t value);
void __asm_outd(uint16_t port, uint32_t value);
uint8_t __asm_inb(uint16_t port);
uint16_t __asm_inw(uint16_t port);
uint32_t __asm_ind(uint16_t port);
uint32_t __asm_get_cr2();

/* x86 cpuid functions */
uint32_t __asm_getcpumaxid(void);
void __asm_getcpustring(char *);
void __asm_getcpubrandstring(char *);

#endif
