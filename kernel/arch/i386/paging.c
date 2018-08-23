#include <kernel/paging.h>

void blank_page_dir(uint32_t* page_directory)
{
    for (int i = 0; i < PAGE_DIR_SIZE; i++) {
        // Flags: Supervisor, Write Enabled, Not Present (in Mem, for removing space needs)
        page_directory[i] = 0x00000002;
    }
}

void blank_page_table(uint32_t* page_table)
{
    // fill all 1024 entries in the table, mapping 4 megabytes
    for (unsigned int i = 0; i < PAGE_TAB_SIZE; i++) {
        // As the address is page aligned, it will always leave 12 bits zeroed (used by attributes).
        // attributes: supervisor level, read/write, present
        page_table[i] = (i * 4096) | 3;
    }
}

void* get_physaddr(void* virtualaddr)
{
    uint32_t pdindex = (uint32_t) virtualaddr >> 22;
    uint32_t ptindex = (uint32_t) virtualaddr >> 12 & 0x03FF;
 
    //extern uint32_t* page_directory;
    //uint32_t* pd = (uint32_t*) page_directory;

    extern uint32_t* master_page_table;
    uint32_t* pt = ((uint32_t*) master_page_table) + (1024 * pdindex);
    // Check whether the PT entry is present.
 
    return (void*) ((pt[ptindex] & ~0xFFF) + ((uint32_t) virtualaddr & 0xFFF));
}