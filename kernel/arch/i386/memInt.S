
.section .data
gdtloc:
    .short 0 # GDT limit address storage
    .int 0   # GDT base address storage

far_jump_address:
    # Example: ljmp $0x8, $refreshGdt
    .short 0 # Segment storage
    .int 0   # Address offset storage

.section .text
    .global loadGdt
    .global enablePaging

loadGdt:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    mov %eax, (gdtloc+2)
    mov 12(%esp), %ax
    mov %ax, (gdtloc)
    lgdt (gdtloc)
    mov %ebp, %esp
    pop %ebp
    # Broken far jump
    # mov $0x8, %ax
    # mov %ax, (far_jump_address)
    # mov $far_jump_address, %eax
    # mov %eax, (far_jump_address+2)
    # ljmp (far_jump_address)
refreshGdt:
    # 0x18 -> 3rd segment descriptor
    mov $0x18, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret

enablePaging:
    push %ebp
    mov %esp, %ebp
    # Load Page Dir Address
    mov 8(%esp), %eax
    mov %eax, %cr3
    # Activate Paging
    mov %cr0, %eax
    or $0x80000001, %eax # activate 32 bit of cr0
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret

# (4 MiB pages)
enablePSE:
    mov %cr4, %eax
    or %eax, 0x00000010
    mov %cr4, %eax
    ret