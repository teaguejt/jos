#ifndef __JOS_KTYPES_H__
#define __JOS_KTYPES_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;

#define LOW_16(addr)  ((uint16_t)(addr & 0xFFFF))
#define HIGH_16(addr) ((uint16_t)((addr >> 16) & 0xFFFF))
#define LOW_32(addr)  ((uint32_t)((addr >> 32) & 0xFFFFFFFF))
#define HIGH_32(addr) ((uint32_t)(addr & 0xFFFFFFFF));

#endif
