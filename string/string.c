#include "string.h"

int strlen( const char *str ) {
    int len;

    for( len = 0; str[len] != '\0'; len++ )
        ;

    return len;
}

int strcmp(const char *str1, const char *str2) {
    int diff = 0;
    int i;

    for(i = 0; i < strlen(str1); i++) {
        if(str2[i] == '\0')
            return -1;

        diff = str1[i] - str2[i];
        if(diff != 0)
            break;
    }
    if(str2[i] != '\0')
        return 1;

    return diff;
}
