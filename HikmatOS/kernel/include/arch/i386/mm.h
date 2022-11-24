#include <stdint.h>
#include <arch/i386/multiboot.h>

#define MMAP_GET_NUM 0
#define MMAP_GET_ADDR 1

void init_mm(multiboot_info_t *mboot_hdr, uint32_t mboot_reserved_start, uint32_t mboot_reserved_end);
uint32_t mmap_read(uint32_t request, uint8_t mode);
uint32_t allocate_frame();
void *kalloc(uint32_t size);

