#ifndef __JOS_BDA_H__
#define __JOS_BDA_H__

#include <ktypes.h>

/* Some stuff to pull BDA info. This gives us I/O ports for serial ports,
   parallel ports, some video mode info, etc. I don't think it's super useful
   in paged mode, but it's a good thing to have. At the very least it lets us
   get a definite answer about some video information. */
#define BDA_BEGIN       0x0400
#define BDA_DISP_COLS   0x044A
#define BDA_DISP_PORT   0x0463  /* I like how well-aligned this addr is */
#define BDA_MAX_COMS    4
#define BDA_MAX_LPTS    3       /* Technically 4 on non PS/2 systems. */
/* Thought: what would you possibly do with a fourth parallel port? */

typedef struct {
    uint16_t com_ports[BDA_MAX_COMS];   /* Ports for COM ports */
    uint16_t lpt_ports[BDA_MAX_LPTS];   /* Ports for parallel */
    uint16_t ebda_addr;                 /* ADDRESS of EBDA */
    uint16_t hardware;                  /* Hardware bit flags */
    uint16_t kbd_states;                /* Keyboard states */
    uint8_t  kbd_buf[4];                /* Keyboard buffer */
    uint8_t  display_mode;
    uint16_t display_cols;
    uint16_t vid_port;                  /* VGA base port */
    uint16_t boot_jiffies;              /* Ticks since boot */
    uint8_t  num_hdds;                  /* Number of hard drives. */
    uint16_t kbd_buf_begin;
    uint16_t kbd_buf_end;
    uint8_t  kbd_state;
} bda_info_t;

void populate_bda_struct();
void display_bda_info();

#endif
