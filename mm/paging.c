/* paging.c - basic paging functions and such */
/* also, the page tables */

#include <mm.h>

#include <interrupts.h>

#ifdef i386
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
    kprintf("error code: 0x%lx\n", t->err_code);
    while(1);
}

void init_paging() {
    register_interrupt_handler(14, (isr_t)page_fault);
}
#endif
