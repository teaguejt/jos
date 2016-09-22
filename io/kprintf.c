#include "kprintf.h"
#include "../screen/kscreen.h"
#include "../string/string.h"
#include "../stdlib/stdarg.h"
#include "../stdlib/stdbool.h"

#define WTBB  0x0F         /* White text, black bg */
#define RTWB  0xF4         /* Red text, white bg */

#define VMTRANSLATE( row, col ) ( VMEM * 2 * 80 * row + col )

static char _attr = WTBB;

/* Static functions */
void kputc( int, int, char );
int kprint_int( int, int, int );
int kprint_hex( int, int, unsigned int );
void kput_hexc( int, int, unsigned int );

void kprinttest() {
    char *vmem = (char *)VMEM;
    *vmem = 'X';
    *(++vmem) = RTWB;
}

/* printf for colored/attributed text */
void kcprintf( const char attr, const char *str, ... ) {
    int xpos, ypos, len, i;
    va_list args;

    va_start( args, str );
    _attr = attr;
    // Get the cursor position
    xpos = sys_get_cursorx();
    ypos = sys_get_cursory();

    // Print the string
    len = strlen( str );
    for( i = 0; i < len; i++ ) {
        switch( str[i] ) {
            case '\n':
                xpos = 0;
                ++ypos;
                break;
            case '%':
                ++i;
                switch( str[i] ) {
                    case 'd':
                        xpos += kprint_int( xpos, ypos, va_arg( args, int ) );
                        break;
                    case 'x':
                        xpos += kprint_hex( xpos, ypos, va_arg( args, unsigned int ) );
                        break;
                    case 'c':
                        kputc( xpos, ypos, va_arg( args, char ) );
                        ++xpos;
                        break;
                }
                break;
            default:
                kputc( xpos, ypos, str[i] );
                ++xpos;
                break;
        }
    }

    // Re-set the cursor position
    sys_set_cursorx( xpos );
    sys_set_cursory( ypos );
    _attr = WTBB;
}

/* The main printf, that actually handles, you know, printing */
void kprintf( const char *str, ... ) {
    int xpos;
    int ypos;
    int len, i;

    va_list args;
    va_start( args, str );
    // Get the cursor position
    xpos = sys_get_cursorx();
    ypos = sys_get_cursory();

    // Print the string
    len = strlen( str );
    for( i = 0; i < len; i++ ) {
        switch( str[i] ) {
            case '\n':
                xpos = 0;
                ++ypos;
                break;
            case '%':
                ++i;
                switch( str[i] ) {
                    case 'd':
                        xpos += kprint_int( xpos, ypos, va_arg( args, int ) );
                        break;
                    case 'x':
                        xpos += kprint_hex( xpos, ypos, va_arg( args, unsigned int ) );
                        break;
                    case 'c':
                        kputc( xpos, ypos, va_arg( args, char ) );
                        ++xpos;
                        break;
                }
                break;
            default:
                kputc( xpos, ypos, str[i] );
                ++xpos;
                break;
        }
    }

    // Re-set the cursor position
    sys_set_cursorx( xpos );
    sys_set_cursory( ypos );
}

void kputc( int xpos, int ypos, char c ) {
    char *addr = ( (char *)VMEM + ( 160 * ypos ) + ( 2 * xpos ) );
    switch( c ) {
        default:
            *addr++ = c;
            /* *addr++ = _attr; */
            *addr++ = 0x0F;
    }
}

int kprint_int( int xpos, int ypos, int i ) {
    int len = 0;
    int it;

    if( i < 0 ) {
        kputc( xpos, ypos, '-' );
        ++xpos;
        ++len;
        i *= -1;
    }

    for( it = 1000000000; it > 0; it /= 10 ) {
        if( i / it != 0 || it == 1 ) {
            kputc( xpos, ypos, i / it + '0' );
            ++xpos;
            ++len;
        }
        i %= it;
    }

    return len;
}

int kprint_hex( int xpos, int ypos, unsigned int i ) {
    int len = 0;
    unsigned int it;
    char *x = (char *)&i;
    char l;
    char h;

    x += sizeof( int ) - 1;
    for( it = 0; it < sizeof( int ); it++ ) {
        l = ( *(char *)x & 15 );
        h = ( *(char *)x & 240 ) >> 4;
        kput_hexc( xpos, ypos, h );
        kput_hexc( xpos + 1, ypos, l );
        xpos += 2;
        len += 2;
        --x;
    }

    return len;
}

void kput_hexc( int xpos, int ypos, unsigned int x ) {
    char c;

    switch( x ) {
        case 10:
            c = 'A';
            break;
        case 11:
            c = 'B';
            break;
        case 12:
            c = 'C';
            break;
        case 13:
            c = 'D';
            break;
        case 14:
            c = 'E';
            break;
        case 15:
            c = 'F';
            break;
        default:
            c = x + '0';
            break;
    }
    kputc( xpos, ypos, c );
}
