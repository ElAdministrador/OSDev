#include <kernel/mem_init.h>

void init_gdt()
{
    // null descriptor
    create_segment_descriptor((uint8_t*) &GDT[0], 0x0, 0x0, 0x0);
    
    // kernel code aligned together (32 bit) with kernel data segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+16, 0x0, 0xfffff, (GDT_CODE_PL0));
    // kernel data segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+24, 0x0, 0xfffff, (GDT_DATA_PL0));
    
    // user code aligned together (32 bit) with user data segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+32, 0x0, 0xfffff, (GDT_CODE_PL3));
    // user data segment descriptor
    create_segment_descriptor((uint8_t*) GDT_BASE_ADDRESS+48, 0x0, 0xfffff, (GDT_DATA_PL3));

    // Initialize GDT
    loadGdt((uint32_t) GDT_BASE_ADDRESS,(uint16_t) GDT_LIMIT_ADDRESS);
}

void init_paging()
{
    // Clear out memory for page directory and master page table
    blank_page_dir((uint32_t*) &page_directory);
    blank_page_table((uint32_t*) &master_page_table);

    // Set the so far only page table reference to the page directory
    page_directory[0] = ((unsigned int) master_page_table) | 3;

    // Activate paging
    enablePaging((uint32_t) &page_directory);
}
