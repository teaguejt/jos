#include <timer.h>
#include "initialize.h"
#include "ktypes.h"
#include "arch.h"
#include "cpu.h"
#include "interrupts.h"
#include "../io/kprintf.h"
#include "../screen/kscreen.h"
#include <meminfo.h>

const char *welcome = "Hello from C code!";
static struct cpu_info cpu_info;
static struct uptime_struct uptime;

/* Control variables */
int should_react = 0;

uint32_t __asm_test(uint32_t);

void dummy(int x, int y, int z) {
    kprintf("stack test: %d %d %d\n", x, y, z);
}

void __update_status_bar() {
    int i;
    int mode = 0x1E;
    sys_screen_enter_status_mode();
    for(i = 0; i < 80; i++)
        kcprintf(mode, " ");
    sys_set_cursorx(35);
    kcprintf(mode, "VoidStar");

    sys_set_cursorx(69);
    /* printf field lengths should come next! */
    if(uptime.days < 10)
        kcprintf(mode, "0%d:", uptime.days);
    else
        kcprintf(mode, "%d:", uptime.days);
    
    if(uptime.hours < 10)
        kcprintf(mode, "0%d:", uptime.hours);
    else
        kcprintf(mode, "%d:", uptime.hours);

    if(uptime.minutes < 10)
        kcprintf(mode, "0%d:", uptime.minutes);
    else
        kcprintf(mode, "%d:", uptime.minutes);

    if(uptime.seconds < 10)
        kcprintf(mode, "0%d", uptime.seconds);
    else
        kcprintf(mode, "%d", uptime.seconds);

    sys_screen_exit_status_mode();
}

void kmain() {
    int i;
    sys_set_cursorx(0);
    sys_set_cursory(7);
    kprintf("Welcome to");
    kcprintf(0x17, " VoidStar \n");
    isr_install();
    kprintf("sizeof long: %d\n", (int)sizeof(long));
    get_mem_info();
    init_uptime_struct(&uptime);
    timer_init(1193);
    __update_status_bar();
    while(1) {
        if(should_react) {
            uptime.cseconds++;
            if(uptime.cseconds == 100) {
                uptime.cseconds = 0;
                uptime_inc_second(&uptime);
                __update_status_bar();
            }
            should_react = 0;
        }
    }
#if 0
    int i;
    /*char * c;*/
    unsigned short pos = 1920;
    uint16_t *bda_tmp;
    uint32_t tmp;
    struct bda_info bda_info;
    struct registers registers;

    isr_install();
    /*kcprintf( 0xF4, welcome );
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
    dummy(1, 2, 3);
    c = (char *)VMEM_LAST_LINE;
    *c++ = 'J';
    *c++ = 0xF;*/
    kprintf("welcome string (rodata) addr = 0x%x\n", welcome);   
    kprintf("jOS System Summary from BDA:\n");
    kprintf("============================\n");
    kprintf("cursor: %x, %x\n", sys_get_cursorx_addr(), sys_get_cursory_addr());
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
    __asm_outb(0x3D4, 0x0F);
    __asm_outb(0x3D5, (unsigned char)(pos & 0xFF));
    __asm_outb(0x3D4, 0x0E);
    __asm_outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
    get_cpu_data(&cpu_info);
    kprintf("Max cpuid eax value = 0x%x\n", cpu_info.max_capabilities);
    //kprintf("IDT array located at 0x%x\n", __get_idt());
    kprintf("int size = %d\n", sizeof(int));
    kprintf("CPU vendor: %s\n", cpu_info.vendor_string);
    kprintf("CPU brand string: %s at 0x%x\n", cpu_info.brand_string, &cpu_info);
    kprintf("location of isr3: 0x%x\n", isr3);
    kprintf("location of timer_init: 0x%x\n", timer_init);
    kprintf("location of kernel pgd: 0x%lx\n", &k_pgd);
    kprintf("size of pgd_struct: 0x%x\n", (int)sizeof(pgd_t));
    timer_init(1193);
    __asm__ __volatile__ ("int $2");
    __asm__ __volatile__ ("int $3");
    while(1) ;
#endif
}
