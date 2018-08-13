
.section .text
    .global loadGdt

loadGdt:
    xor %eax,%eax
    mov -4(%esp), %eax
    ret