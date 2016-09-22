#include "../io/kprintf.h"
#include "../screen/kscreen.h"

const char *welcome = "Hello from C code!";

void dummy() {
}

void kmain() {
    kprintf("cursor: %d, %d\n", sys_get_cursorx(), sys_get_cursory());
    kprintf("cursor: %x, %x\n", sys_get_cursorx_addr(), sys_get_cursory_addr());
    //kcprintf( 0xF4, welcome );
    //kprintf("cursor: %d, %d\n", x, y);
    //kcprintf( 0x0F, "\nNEW LINE TEST\n" );
    kprintf( "%d Zero int test\n", 0 );
    //kprintf( "%d Non-zero int test\n", 5 );
    //kprintf( "%d Negative test\n", -6 );
    //kprintf( "%d %d Multiple arg test\n", 1, -1 );
    //kprintf( "%d %d Long int test\n", 123, 1234567890 );
    //kprintf( "0x%x Hex test\n", 52 );
    //kcprintf( 0xF4, "%c %c %d Char test\n", 'c', 'd', 128 );
    //kcprintf( 0xF4, "%d %x Attributed test\n", 500, 128 );
    while(1) ;
}
