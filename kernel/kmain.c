#include <timer.h>
#include "initialize.h"
#include "ktypes.h"
#include "arch.h"
#include "cpu.h"
#include "interrupts.h"
#include "../io/kprintf.h"
#include "../screen/kscreen.h"
#include <meminfo.h>
#include "../io/keyboard.h"
#include <mm.h>
#include <list.h>

#ifdef i386
#include <bda.h>
#endif

static struct cpu_info cpu_info;
static struct uptime_struct uptime;

/* Control variables */
int should_react = 0;

uint32_t __asm_test(uint32_t);

void dummy(int x, int y, int z) {
    kprintf("stack test: %d %d %d\n", x, y, z);
}

void get_cpu_info() {
    struct cpu_info cpu_info;
    get_cpu_data(&cpu_info);
    kcprintf(0x1E, "Detected CPU Information:\n");
    kprintf("Max cpuid eax value = 0x%x\n", cpu_info.max_capabilities);
    kprintf("IDT array located at 0x%x\n", __get_idt());
    kprintf("int size = %d\n", sizeof(int));
    kprintf("CPU vendor: %s\n", cpu_info.vendor_string);
    kprintf("CPU brand string: %s at 0x%x\n\n", cpu_info.brand_string, &cpu_info);
}

void help() {
    kcprintf(0x1E, " VOIDSTAR ");
    kprintf(" Help\n\n");
    kprintf("This is an early version. Nothing is fully implemented.\n");
    kprintf("\"Shell\" commands:\n");
    kprintf("CLR:  clear the screen\n");
    kprintf("BDA:  display BIOS Data Area information\n");
    kprintf("CPU:  display CPU information\n");
    kprintf("MEM:  display E820 map and memory usage information.\n");
    kprintf("HELP: display this.\n");
}

void __update_status_bar() {
    int i;
    int mode = 0x1E;
    sys_screen_enter_status_mode();
    for(i = 0; i < 80; i++)
        kcprintf(mode, " ");
    sys_set_cursorx(33);
    kcprintf(mode, "| VoidStar |");

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

    sys_set_cursorx(0);
    kcprintf(mode, "-> ");
    kcprintf(mode, shell_buf);

    sys_screen_exit_status_mode();
}

void kmain() {
    int i;
    sys_init_hw_cursor();
    sys_set_cursorx(0);
    sys_set_cursory(7);
    kprintf("Welcome to");
    kcprintf(0x1E, " VoidStar \n");
    isr_install();
    //get_mem_info();
    init_uptime_struct(&uptime);
    timer_init(1193);
    __update_status_bar();
    keyboard_init();
    init_paging();
    populate_bda_struct();
    //*(int *)0xC5000000 = 50;
    while(1) {
        if(should_react) {
            uptime.cseconds++;
            if(uptime.cseconds == 100) {
                uptime.cseconds = 0;
                uptime_inc_second(&uptime);
            }
            if(pending_cmd == 1) {
                kprintf("\n\n");
                if(strcmp(shell_buf, "MEM") == 0)
                    get_mem_info();
                else if(strcmp(shell_buf, "CPU") == 0)
                    get_cpu_info();
                else if(strcmp(shell_buf, "CLR") == 0)
                    sys_clear_screen();
                else if(strcmp(shell_buf, "BDA") == 0)
                    display_bda_info();
                else if(strcmp(shell_buf, "LIST-TEST") == 0) {
                    test_llist();
                }
                else if(strcmp(shell_buf, "HELP") == 0)
                    help();
                else
                    kprintf("Invalid command: %s\n", shell_buf);
                pending_cmd = 0;
                for(i = 0; i < 32; i++) {
                    shell_buf[i] = '\0';
                }
            }
            __update_status_bar();
            should_react = 0;
            /* Induce a page fault */
            //kprintf("0x%lx\n", *(unsigned long *)0xD0000000);
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
    /*kcprintf( 0xF4, welcome );*/
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
