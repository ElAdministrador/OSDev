#include <kernel/mem_init.h>

void init_gdt() {

    // Initialize GDT
    loadGdt((uint32_t) GDT_BASE_ADDRESS,(uint16_t) GDT_LIMIT_ADDRESS);
    
    // null descriptor
    create_segment_descriptor((uint8_t*) &GDT[0], 0x0, 0x0, 0x0);
    
    // kernel code segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+16, 0x0, 0xfffff, (GDT_CODE_PL0));
    // kernel data segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+24, 0x0, 0xfffff, (GDT_DATA_PL0));
    
    // user code segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+32, 0x0, 0xfffff, (GDT_CODE_PL3));
    // user data segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+40, 0x0, 0xfffff, (GDT_DATA_PL3));

};