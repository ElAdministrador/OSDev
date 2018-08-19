
.section .data
gdtloc:
    .short 0 # GDT limit address storage
    .int 0   # GDT base address storage

.section .text
    .global loadGdt
    .global enablePaging

loadGdt:
    push %ebp
    mov %esp, %ebp
    mov 8(%esp), %eax
    mov %eax, gdtloc+2
    mov 12(%esp), %ax
    mov %ax, gdtloc
    lgdt gdtloc
    mov %ebp, %esp
    pop %ebp
    ret
    
enablePaging:
    push %ebp
    mov %esp, %ebp
    mov %cr0, %eax
    or $0x80000001, %eax # activate 32 bit of cr0
    mov %eax, %cr0
    mov %ebp, %esp
    pop %ebp
    ret