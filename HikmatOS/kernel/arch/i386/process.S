.global read_eip
.type read_eip, @function
read_eip:
    pop %eax
    jmp %eax

.global copy_page_physical
.type copy_page_physical, @function
copy_page_physical:
    push %ebx
    pushf

    cli

    mov 12(%esp), %ebx
    mov 16(%esp), %ecx

    mov %cr0, %edx
    and $0x7fffffff, %edx
    mov %edx, %cr0

    mov $1024, %edx

.loop:
    mov (%ebx), %eax
    mov %eax, (%ecx)
    add $4, %ebx
    add $4, %ecx
    dec %edx
    jnz .loop

    mov %cr0, %edx
    or $0x80000000, %edx
    mov %edx, %cr0

    popf
    pop %ebx
    ret

.global perform_task_switch
.type perform_task_switch, @function
perform_task_switch:
    cli
    mov 4(%esp), %ecx
    mov 8(%esp), %eax
    mov 12(%esp), %ebp
    mov 16(%esp), %esp
    mov %eax, %cr3
    mov $0x12345, %eax
    sti
    jmp *%ecx

