#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "hello_world.h"

void hello(char *buffer, const char *name)
{
    strcpy(buffer, "");

    if (name == NULL) {
        strcpy(buffer, "Hello, World!");
    } else {
        strcat(buffer, "Hello, ");
        strcat(buffer, name);
        strcat(buffer, "!");
    }
}
