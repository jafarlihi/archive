#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/task.h>
#include <kernel/fs.h>
#include <arch/i386/multiboot.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/irq.h>
#include <arch/i386/timer.h>
#include <arch/i386/keyboard.h>
#include <arch/i386/mm.h>

uint32_t initial_esp;

void kernel_main(uint32_t mboot_magic, void *mboot_header, uint32_t initial_stack) {
    initial_esp = initial_stack;

    if (mboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Error: We weren't booted by a compliant bootloader!\n");
        return;
    }

    multiboot_info_t *mboot_hdr = (multiboot_info_t *)mboot_header;

    if ((mboot_hdr->flags & (1<<6)) == 0) {
        printf("Error: No Multiboot memory map was provided!\n");
        return;
    }

    init_mm(mboot_hdr, (uint32_t)mboot_hdr, (uint32_t)(mboot_hdr + sizeof(multiboot_info_t)));

    terminal_initialize();

    init_gdt();
    printf("GDT initialized\n");
    init_idt();
    printf("IDT initialized\n");
    init_irq();
    printf("IRQ initialized\n");

    timer_phase(100);
    init_timer();
    printf("Timer initialized\n");

    init_keyboard();
    printf("Keyboard initialized\n");

    init_paging();
    printf("Paging enabled\n");

    init_tasking();
    printf("Tasking initialized\n");

    init_fs();
    printf("FS initialized\n");

    int ret = fork();
    if (ret == 0) {
        printf("Printing from child\n"); // TODO: Why returning from child break IRQs?
    } else {
        printf("Printing from parent\n");
        printf("Waiting 100 ticks\n");
        timer_wait(100);
        printf("Finished waiting\n");
    }

    while (1) {}
}

