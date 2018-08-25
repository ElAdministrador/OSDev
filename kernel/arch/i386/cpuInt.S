
.section .text
    .global checkCPUID

# Check if cpuid operation is available
checkCPUID:
    push %ebp
    mov %esp, %ebp
    pushfl                # save current EFlags register on stack
    pushfl                # push EFlags again
    pop %edx
    xor $0x200000, %edx   # invert ID flag (bit 21) of EFlags
    push %edx
    popfl                 # pop back into EFlags
    pushfl                # check if AC bit may be inverted
    pop %eax
    xor (%esp), %eax      # compare former eax to modified
    popfl                 # restore former Eflags
    and $0x200000, %eax    
    shr $21, %eax         # eax = CPUID available
    pop %ebp
    ret