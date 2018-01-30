#include "keyboard.h"

#define SCAN_MAX  0x34
#define ENTER     0x1C
#define BACKSPACE 0x0E

/* The keyboard controller converts the actual keyboard scancode
   set to set 1, so we're just going to use that. This is a 
   STRIPPED DOWN version, that allows us to get use input so we can
   implement and develop the memory manager and system call 
   framework. A full driver cannot exist until those things do. */
static char *__kbd_scancodes[] = {"error", "esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "backspace", "tab", "Q", "W", "E", "R", "T",
    "Y", "U", "I", "O", "P", "[", "]", "enter", "lctrl", "A", "S", "D", "F",
    "G", "H", "J", "K", "L", ";", "'", "`", "lshift", "\\", "Z", "X", "C", "V",
    "B", "N", "M", ",", "."};

static char __kbd_sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
    ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.'};

char shell_buf[64];
static int buf_len = 0;

static void keyboard(registers_t t) {
    uint8_t scancode;

    scancode = __asm_inb(0x60);
    if(scancode > SCAN_MAX) return;
    else if(scancode == ENTER) {
        shell_buf[0] = '\0';
        for(buf_len = 0; buf_len < 64; buf_len++) {
            shell_buf[buf_len] = '\0';
        }
        buf_len = 0;
    }
    else if(scancode == BACKSPACE) {
        buf_len--;
        if(buf_len < 0) buf_len = 0;
        shell_buf[buf_len] = '\0';
    }
    else {
        if(buf_len == 63) return;
        shell_buf[buf_len] = __kbd_sc_ascii[scancode];
        ++buf_len;
    }
    //kprintf("scancode: 0x%lx\n", scancode);
}

static int get_scancode_set() {
    uint8_t cmd = 0xF0;
    uint8_t prm = 0x00;
    uint8_t res = 0;

    __asm_outb(0x60, cmd);
    /* Output to the keyboard requesting scancode set */
    do {
        /* Read input. Wait for ack (0xFA) or resent (0xFE) */
        res = __asm_inb(0x60);
        if(res == 0xFA)
            break;
        else if(res == 0xFE)
            __asm_outb(0x60, cmd);
    } while(1);

    /* Output parameter to keyboard */
    res = 0;
    __asm_outb(0x60, 0x2);
    do {
        res = __asm_inb(0x60);
        if(res == 0xFA)
            break;
        else if(res == 0xFE)
            __asm_outb(0x60, cmd);
    } while(1);
    __asm_outb(0x60, cmd);
    
    /* Output to the keyboard requesting scancode set */
    do {
        /* Read input. Wait for ack (0xFA) or resent (0xFE) */
        res = __asm_inb(0x60);
        if(res == 0xFA)
            break;
        else if(res == 0xFE)
            __asm_outb(0x60, cmd);
    } while(1);

    /* Output parameter to keyboard */
    res = 0;
    __asm_outb(0x60, prm);
    do {
        res = __asm_inb(0x60);
        if(res == 0xFA)
            break;
        else if(res == 0xFE)
            __asm_outb(0x60, cmd);
    } while(1);

    /* Received ack, now wait for scancode set identifer. */
    do {
        res = __asm_inb(0x60);
    } while(res == 0xFE);

    return res;
}

void keyboard_init() {
    int set;

    set = get_scancode_set();
    kprintf("keyboard initialized: scancode set = 0x%lx\n", set);
    kprintf("shell buffer = 0x%lx\n", shell_buf);
    register_interrupt_handler(IRQ1, &keyboard);
}
