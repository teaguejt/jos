#ifndef __JOS_IDT_H__
#define __JOS_IDT_H__

#define KERNEL_SEGMENT 0x08

typedef struct {
    uint16_t low;
    uint16_t seg;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t high;
} __attribute__(packed) __idt_gate;



#endif
