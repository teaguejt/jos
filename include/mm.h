#ifndef __JOS_MM_H__
#define __JOS_MM_H__

#include <kernel.h>
#include <ktypes.h>
#include <interrupts.h>
#include <arch.h>
#include <cpu.h>

#ifdef i386

#define PAGE_SIZE   4096
#define OFFSET_BITS 12
#define TBL_ENTRIES 1024
#define ENTRY_SIZE  4

/* Hard-coded addresses for the kernel's reserved memory structures. */
#define KERN_PGD    0x3000
#define LOW_PGT     0x4000
#define KERN_PGT    0x5000

/* A page directory table. It's pretty much an array
   of unsigned integers */
typedef struct {
    uint32_t dirs[1024];
} pgd_t;


#define DIR_IN_USE(dir) \
    ((uint32_t)dir & 0x00000001)

#define DIR_RW_MODE(dir) \
    ((uint32_t)dir & 0x00000002)

#define DIR_PERMISSIONS(dir) \
    ((uint32_t)dir & 0x00000004)

#define DIR_SIZE(dir) \
    ((uint32_t)dir & 0x00000080)

#define DIR_PADDR(dir) \
    ((uint32_t)dir & 0xFFFFF000)

typedef uint32_t pte_t;

/* A page table. Pretty much the same as a PGD */
typedef struct {
    pte_t ptes[1024];
} pgt_t;

#define ENT_IN_USE(ent) \
    ((uint32_t)ent & 0x00000001)

#define ENT_RW_MODE(ent) \
    ((uint32_t)ent & 0x00000002)

#define ENT_PERMISSIONS(ent) \
    ((uint32_t)ent & 0x00000004)

#define ENT_SIZE(ent) \
    ((uint32_t)ent & 0x00000080)

#define ENT_PADDR(ent) \
    ((uint32_t)ent & 0xFFFFF000)

/* Kernel memory structures for management */
typedef struct {
    uint32_t base;  // Starting address of memory region
    uint32_t limit; // Last page of memory region
    uint32_t ptr;   // Current position of usage within region
} phys_mem_region;

void init_paging();

#endif /* i386 */
#endif
