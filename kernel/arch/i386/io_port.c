#include <kernel/io_port.h>

void outb(uint16_t adr, uint8_t value) {
    
    asm volatile(
        "out %0, %1"
        :                        /* ass output operands */
        : "a"(value), "Nd"(adr)  /* ass input operands */
    );
}

uint8_t inb(uint16_t adr) {
    
    uint8_t ret;
    asm volatile(
        "in %1, %0"
        : "=a"(ret)  /* ass output operands */
        : "Nd"(adr)  /* ass input operands */
    );
    
    return ret;
}