#ifndef __JOS_KSCREEN_H__
#define __JOS_KSCREEN_H__

#ifdef i386
#define VMEM (0xB8000)
#define VMEM_MAX (0xB8F9E)
#define VMEM_END (0xB8F9A)
#define VMEM_LINE_SIZE (0xA0)
#define VMEM_MAX_LINE (24)
#define VMEM_LAST_LINE (0xB8F00)
#endif

void sys_clear_screen();
void sys_set_cursorx( int );
void sys_set_cursory( int );
int sys_get_cursorx();
int sys_get_cursory();
int *sys_get_cursorx_addr();
int *sys_get_cursory_addr();
void sys_scroll_term();
int sys_cursor_overflow(int);
/*void ksetcursor( int, int );
int *kgetcursor();*/

void sys_screen_enter_status_mode();
void sys_screen_exit_status_mode();

#endif
