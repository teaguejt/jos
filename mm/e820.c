#include <meminfo.h>
#include <mm.h>
#include "../screen/kscreen.h"

#ifdef i386

static int mem_regions;
static char *region_types[3] = {"UNDEF", "AVAIL", "RSRVD"};
static char *dir_modes[2]    = {"RO", "RW"};
static char *dir_perms[2]    = {"USER", "KERN"};
static char *dir_sizes[2]    = {"4k", "4M"};

void get_mem_regions() {
    mem_regions = *(uint16_t *)0x2400;
}

void get_mem_info() {
    int i, j, count;
    unsigned int tot = 0;
    uint32_t base;
    uint32_t sz;
    void *addr;
    e820_info *info;
    pgd_t *kpgd;
    pgt_t *pgt;

    base = 0x2000;
    sz   = 0x18;
    get_mem_regions();
    if(mem_regions == 0) {
        kprintf("fatal error: no memory regions\n");
        return;
    }

    addr = (void *)base;
    kprintf("e820 reporting %d memory regions:\n", mem_regions);
    for(i = 0; i < mem_regions; i++) {
        info = (e820_info *)addr;
        kprintf("region %d: ", i + 1);
        kprintf("0x%lx bytes at 0x%lx ", info->size_low, info->base_low);
        if(info->type > 2)  info->type = 0;
        kprintf("%s\n", region_types[info->type]);
        addr += sz;
        if(info->type == 1)
            tot += (info->size_low - info->base_low);
    }
    kprintf("Total system memory: 0x%lx bytes\n", tot);
    
    kprintf("\npgd info:\n");
    kpgd = (pgd_t *)0x3000;
    for(i = 0; i < TBL_ENTRIES; i++) {
        if(DIR_IN_USE(kpgd->dirs[i])) {
            kprintf("%d: ", i);
            sys_set_cursorx(6);
            if(DIR_RW_MODE(kpgd->dirs[i]))
                kprintf("%s     ", dir_modes[1]);
            else
                kprintf("%s     ", dir_modes[0]);
            if(DIR_PERMISSIONS(kpgd->dirs[i]))
                kprintf("%s     ", dir_perms[1]);
            else
                kprintf("%s     ", dir_perms[0]);
            if(DIR_SIZE(kpgd->dirs[i]))
                kprintf("%s     ", dir_sizes[1]);
            else
                kprintf("%s     ", dir_sizes[0]);
            kprintf("0x%lx     ", DIR_PADDR(kpgd->dirs[i]));

            count = 0;
            pgt = (pgt_t *)DIR_PADDR(kpgd->dirs[i]);
            for(j = 0; j < TBL_ENTRIES; j++) {
                if ENT_IN_USE(pgt->ptes[j])
                    ++count;
            }

            kprintf("%d", count);
            sys_set_cursorx(48);
            kprintf(" / %d", (int)TBL_ENTRIES);

            kprintf("\n");
        }
    }
}

#endif /* i386 */
