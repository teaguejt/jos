#ifndef __JOS_KERNEL_H__
#define __JOS_KERNEL_H__

#include "../string/string.h"

#define UNUSED(x) (void)(x)

extern int should_react;
extern char shell_buf[32];
extern int pending_cmd;

#endif
