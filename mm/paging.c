/* paging.c - basic paging functions and such */
/* also, the page tables */

#include <paging.h>

#ifdef i386
uint32_t k_pgd[1024] __attribute__((aligned(4096)));
#endif
