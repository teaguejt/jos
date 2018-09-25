#ifndef __JOS_KERNEL_H__
#define __JOS_KERNEL_H__

/* Important constants */
#define NULL 0              /* I know, cliche. But it works. */

/* Very important macros. */
#define struct_offset(type, member)                                         \
    (unsigned long)&(((type *)0)->member)

#include "../string/string.h"

#define UNUSED(x) (void)(x)

extern int should_react;
extern char shell_buf[32];
extern int pending_cmd;

#endif
