#include "../io/kprintf.h"
#include "../screen/kscreen.h"

const char *welcome = "Hello from C code!";

void __asm_test(void);

void dummy(int x, int y, int z) {
    kprintf("stack test: %d %d %d\n", x, y, z);
}

void kmain() {
    int i;
    char * c;
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
    for(i = 0; i < 10; ++i)
        kprintf("Scrolling test! %d\n", i);
    c = (char *)VMEM_LAST_LINE;
    *c++ = 'J';
    *c++ = 0xF;
    __asm_test();
    while(1) ;
}
