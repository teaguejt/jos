#ifndef __JOS_KSCREEN_H__
#define __JOS_KSCREEN_H__

#define VMEM (0xB8000)
#define VMEM_MAX (0xB8F9E)
#define VMEM_END (0xB8F9A)

void sys_clear_screen();
void sys_set_cursorx( int );
void sys_set_cursory( int );
int sys_get_cursorx();
int sys_get_cursory();
/*void ksetcursor( int, int );
int *kgetcursor();*/

#endif
