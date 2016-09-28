#include "initialize.h"
#include "ktypes.h"
#include "arch.h"
#include "../io/kprintf.h"
#include "../screen/kscreen.h"


const char *welcome = "Hello from C code!";

uint32_t __asm_test(uint32_t);

void dummy(int x, int y, int z) {
    kprintf("stack test: %d %d %d\n", x, y, z);
}

void kmain() {
    int i;
    char * c;
    uint16_t *bda_tmp;
    uint32_t tmp;
    struct bda_info bda_info;
    struct registers registers;

    kcprintf( 0xF4, welcome );
    kcprintf( 0x0F, "\nNEW LINE TEST\n" );
    kprintf( "%d Zero int test\n", 0 );
    kprintf( "%d Non-zero int test\n", 5 );
    kprintf( "%d Negative test\n", -6 );
    kprintf( "%d %d Multiple arg test\n", 1, -1 );
    kprintf( "%d %d Long int test\n", 123, 1234567890 );
    kprintf( "0x%x Hex test\n", 52 );
    kcprintf( 0xF4, "%c %c %d Char test\n", 'c', 'd', 128 );
    kcprintf( 0xF4, "%d %x Attributed test\n", 500, 128 );
    kprintf("testing printing func retvals and var addresses:\n");
    kprintf("cursor: %d, %d\n", sys_get_cursorx(), sys_get_cursory());
    kprintf("cursor: %x, %x\n", sys_get_cursorx_addr(), sys_get_cursory_addr());
    dummy(1, 2, 3);
    c = (char *)VMEM_LAST_LINE;
    *c++ = 'J';
    *c++ = 0xF;
    
    /* Read the BIOS data area */
    bda_tmp = (uint16_t *)__INIT_BDA;
    for(i = 0; i < 4; i++) {
        bda_info.com_ports[i] = *bda_tmp++;
        kprintf("com port %d: 0x%x\n", i, (int)bda_info.com_ports[i]);
    }
    bda_tmp = (uint16_t *)(0x44A);
    bda_info.display_cols = *bda_tmp;
    kprintf("detected text mode cols: %d\n", (int)bda_info.display_cols);
    bda_tmp = (uint16_t *)(0x463);
    bda_info.vid_port = *bda_tmp;
    kprintf("display port: 0x%x\n", (int)bda_info.vid_port);
    tmp = __asm_test(0xbeef);
    kprintf("0x%x\n", tmp);
    __asm_getreg(&registers); 
    kprintf("eax: 0x%x     ", registers.eax);
    kprintf("ebx: 0x%x\n", registers.ebx);
    kprintf("ecx: 0x%x     ", registers.ecx);
    kprintf("edx: 0x%x\n", registers.edx);
    kprintf("esp: 0x%x\n", registers.esp);
    while(1) ;
}
