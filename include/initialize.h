/* jos - kernel/initialize.h
 * Contains constants and function prototypes needed to boot the system
 * and get memory maps, read from the BDA, etc. */

#ifndef __JOS_INITIALIZE_H__
#define __JOS_INITIALIZE_H__

#define __INIT_BDA  0x0400      /* Memory address of BIOS data area */

/* A struct containing the information from the BDA */
struct bda_info {
    unsigned short com_ports[4];    /* Ports for COM ports */
    unsigned short lpt_ports[3];    /* Ports for parallel */
    unsigned short ebda_addr;       /* ADDRESS of EBDA */
    unsigned short hardware;        /* Hardware bit flags */
    unsigned short kbd_states;      /* Keyboard states */
    unsigned char  kbd_buf[4];      /* Keyboard buffer */
    unsigned char  display_mode;
    unsigned short display_cols;
    unsigned short vid_port;        /* VGA base port */
    unsigned short boot_jiffies;    /* Ticks since boot */
    unsigned char  num_hdds;        /* Number of hard drives. */
    unsigned short kbd_buf_begin;
    unsigned short kbd_buf_end;
    unsigned char  kbd_state;
};

#endif
