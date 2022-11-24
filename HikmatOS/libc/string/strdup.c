#include <string.h>

char *strdup(char *src) {
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = kmalloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

