#ifndef __JOS_MM_H__
#define __JOS_MM_H__

#ifdef i386

#define PAGE_SIZE   4096
#define OFFSET_BITS 12
#define TBL_ENTRIES 1024
#define ENTRY_SIZE  4

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

#endif
#endif
