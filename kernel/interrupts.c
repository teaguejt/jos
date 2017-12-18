#include "interrupts.h"
#include "../io/kprintf.h"

struct idt_entry *__get_idt() {
    return idt;
}

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low   = (uint16_t)(handler & 0xFFFF); 
    idt[n].sel          = KERNEL_CS;
    idt[n].zero         = 0;
    idt[n].type         = 0x8E;
    idt[n].offset_high  = (uint16_t)((handler >> 16) & 0xFFFF);
}

void set_idt() {
    idtr.base   = (uint32_t)&idt;
    idtr.limit  = IDT_ENTRIES * sizeof(struct idt_entry) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idtr));
}

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install() {
    set_idt_gate(0, (uint32_t)isr0);
    set_idt_gate(1, (uint32_t)isr1);
    set_idt_gate(2, (uint32_t)isr2);
    set_idt_gate(3, (uint32_t)isr3);
    set_idt_gate(4, (uint32_t)isr4);
    set_idt_gate(5, (uint32_t)isr5);
    set_idt_gate(6, (uint32_t)isr6);
    set_idt_gate(7, (uint32_t)isr7);
    set_idt_gate(8, (uint32_t)isr8);
    set_idt_gate(9, (uint32_t)isr9);
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

    // Remap the programmable interrupt controller
    __asm_outb(0x20, 0x11);
    __asm_outb(0xA0, 0x11);
    __asm_outb(0x21, 0x20);
    __asm_outb(0xA1, 0x28);
    __asm_outb(0x21, 0x04);
    __asm_outb(0xA1, 0x02);
    __asm_outb(0x21, 0x01);
    __asm_outb(0xA1, 0x01);
    __asm_outb(0x21, 0x00);
    __asm_outb(0xA1, 0x00);

    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r) {
    kprintf("received interrupt: %d\n", (int)r.int_no);
    kprintf("%s\n", exception_messages[r.int_no]);
}
