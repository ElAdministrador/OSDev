
.section .data
gdtloc:
    .short 0 # GDT limit address storage
    .int 0   # GDT base address storage

.section .text
    .global loadGdt

loadGdt:
    mov 4(%esp), %eax
    mov %eax, gdtloc+2
    mov 8(%esp), %ax
    mov %ax, gdtloc
    lgdt gdtloc
    ret
    