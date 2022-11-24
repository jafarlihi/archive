#ifndef _TASK_H
#define _TASK_H

#include <stdint.h>
#include <arch/i386/paging.h>

#define KERNEL_STACK_SIZE 16384

typedef struct task {
    int id;
    uint32_t esp, ebp;
    uint32_t eip;
    page_directory_t *page_directory;
    uint32_t kernel_stack;
    struct task *next;
} task_t;

void init_tasking();
void task_switch();
int fork();
void move_stack(void *new_stack_start, uint32_t size);
int getpid();

#endif

