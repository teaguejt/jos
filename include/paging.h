/* paging.h - structures and externs needed for paging. */

#ifndef __JOS_PAGING_H__
#define __JOS_PAGING_H__

#include <ktypes.h>

#ifdef i386
/* page table entry */
typedef uint32_t pte_t;

/* page table */
typedef struct {
    uint32_t pte_t[1024];
} pgt_t;

/* page directory */
typedef struct {
    uint32_t pgt_t[1024];
} pgd_t;

#endif /* i386 */
#endif
