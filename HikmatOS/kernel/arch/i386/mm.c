#include <arch/i386/mm.h>

#define PAGE_SIZE 4096

multiboot_info_t *verified_mboot_hdr;
uint32_t mboot_reserved_start;
uint32_t mboot_reserved_end;
uint32_t next_free_frame = 1;

void init_mm(multiboot_info_t *_mboot_hdr, uint32_t _mboot_reserved_start, uint32_t _mboot_reserved_end) {
    verified_mboot_hdr = _mboot_hdr;
    mboot_reserved_start = _mboot_reserved_start;
    mboot_reserved_end = _mboot_reserved_end;
}

uint32_t mmap_read(uint32_t request, uint8_t mode) {
    if (request == 0) return 0;

    if (mode != MMAP_GET_NUM && mode != MMAP_GET_ADDR) return 0;

    uintptr_t cur_mmap_addr = (uintptr_t)verified_mboot_hdr->mmap_addr;
    uintptr_t mmap_end_addr = cur_mmap_addr + verified_mboot_hdr->mmap_length;
    uint32_t cur_num = 0;

    while (cur_mmap_addr < mmap_end_addr) {
        multiboot_memory_map_t *current_entry = (multiboot_memory_map_t *)cur_mmap_addr;

        uint64_t i;
        uint64_t current_entry_end = current_entry->addr + current_entry->len;
        for (i=current_entry->addr; i + PAGE_SIZE < current_entry_end; i += PAGE_SIZE) {
            if (mode == MMAP_GET_NUM && request >= i && request <= i + PAGE_SIZE) {
                return cur_num+1;
            }

            if (current_entry->type == MULTIBOOT_MEMORY_RESERVED) {
                if (mode == MMAP_GET_ADDR && cur_num == request) {
                    ++request;
                }
                ++cur_num;
                continue;
            } else if (mode == MMAP_GET_ADDR && cur_num == request) {
                return i;
            }
            ++cur_num;
        }

        cur_mmap_addr += current_entry->size + sizeof(uintptr_t);
    }
    return 0;
}

uint32_t allocate_frame() {
    uint32_t addr = mmap_read(next_free_frame, MMAP_GET_ADDR);

    if (addr >= mboot_reserved_start && addr <= mboot_reserved_end) {
        ++next_free_frame;
        return allocate_frame();
    }

    uint32_t cur_num = mmap_read(addr, MMAP_GET_NUM);

    next_free_frame = cur_num + 1;

    return cur_num;
}

void *kalloc(uint32_t size) {
    uint32_t current_size = 0;
    uint32_t last_address;
    uint32_t new_frame = allocate_frame();
    uint32_t new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
    uint32_t first_address = new_frame_addr;
    while (current_size < size) {
        last_address = new_frame_addr;
        new_frame = allocate_frame();
        new_frame_addr = mmap_read(new_frame, MMAP_GET_ADDR);
        if (last_address + 0x1000 != new_frame_addr) {
            first_address = new_frame_addr;
            current_size = 0;
        }
        current_size += PAGE_SIZE;
    }
    return first_address;
}

