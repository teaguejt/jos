/* paging.c - basic paging functions and such */
/* also, the page tables */

#include <mm.h>

#include <interrupts.h>

#ifdef i386
/* x86 error code bits:
   0 - Type:        0 = non-present page,      1 = protection violation
   1 - Mode:        0 = read,                  1 = write
   2 - Access:      0 = kernel mode,           1 = user mode
   3 - Reserved:    0 = not reserved,          1 = reserved
   4 - Instruction: 0 = not instruction fetch, 1 = instruction fetch
   This should let us reconstruct the cause of the fault and handle it 
   properly */

#define FLT_TYPE(x) (x & 0x1)
#define FLT_MODE(x) (x & 0x2)
#define FLT_ACCS(x) (x & 0x4)
#define FLT_RSVD(x) (x & 0x8)
#define FLT_INST(x) (x & 0x10)

static void page_fault(registers_t *t) {
    uint32_t fault_vaddr;
    pgd_t kpgd;
    pgt_t kpgt;

    kprintf("page fault!\n");
    /* Get the value of the CR2 register (faulting virtual address) */
    fault_vaddr = __asm_get_cr2();
    kprintf("faulting address: 0x%lx\n", fault_vaddr);
    /* You know what seems like a good idea? Spinning in an 
       interrupt service routine. */
    kprintf("TYPE    MODE    ACCS    RSVD    INST\n");
    
    if(FLT_TYPE(t->err_code)) {
        kprintf("PROT    ");
    }
    else {
        kprintf("NONP    ");
    }

    if(FLT_MODE(t->err_code)) {
        kprintf("  WR    ");
    }
    else {
        kprintf("  RD    ");
    }

    if(FLT_ACCS(t->err_code)) {
        kprintf("USER    ");
    }
    else {
        kprintf("KERN    ");
    }

    if(FLT_RSVD(t->err_code)) {
        kprintf(" YES    ");
    }
    else {
        kprintf("  NO    ");
    }

    if(FLT_INST(t->err_code)) {
        kprintf(" YES    ");
    }
    else {
        kprintf("  NO    ");
    }
    kprintf("\n");
    while(1) ;
}

void init_paging() {
    register_interrupt_handler(14, (isr_t)page_fault);
}
#endif
