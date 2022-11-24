#include <stdint.h>
#include <stdio.h>

extern void panic(const char *message, const char *file, uint32_t line) {
    // TODO: Check arch here
    asm volatile("cli");

    printf("PANIC(");
    printf(message);
    printf(") at ");
    printf(file);
    printf(":");
    printf("%d", line);
    printf("\n");

    for(;;);
}

extern void panic_assert(const char *file, uint32_t line, const char *desc) {
    // TODO: Check arch here
    asm volatile("cli");

    printf("ASSERTION-FAILED(");
    printf(desc);
    printf(") at ");
    printf(file);
    printf(":");
    printf("%d", line);
    printf("\n");

    for(;;);
}
