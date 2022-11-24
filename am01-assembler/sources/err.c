#include <stdio.h>
#include <stdarg.h>

#define PASS_VARARGS() \
    va_list args; \
    va_start(args, fmt); \
    print(fmt, args); \
    va_end(args);

char *ANSIC_RED = "\x1b[31m";
char *ANSIC_GREEN = "\x1b[32m";
char *ANSIC_BLUE = "\x1b[34m";
char *ANSIC_RESET = "\x1b[0m";

static void print(char *fmt, va_list args) {
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
}

void printErr(char *fmt, ...) {
    fprintf(stderr, "%s%s%s", ANSIC_RED, "[ERROR] ", ANSIC_RESET);
    PASS_VARARGS();
}

void printInfo(char *fmt, ...) {
    fprintf(stderr, "%s%s%s", ANSIC_BLUE, "[INFO] ", ANSIC_RESET);
    PASS_VARARGS();
}

#ifdef DEBUG
void printDbg(char *fmt, ...) {
    fprintf(stderr, "%s%s%s", ANSIC_GREEN, "[DEBUG] ", ANSIC_RESET);
    PASS_VARARGS();
}
#endif
