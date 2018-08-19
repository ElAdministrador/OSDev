#include <kernel/paging.h>

void blank_page_dir()
{
    for (int i = 0; i < PAGE_DIR_SIZE; i++) {
        // Flags: Supervisor, Write Enabled, Not Present (in Mem, for removing space needs)
        page_directory[i] = 0x00000002;
    }
}

void fill_first_page_table()
{
    // fill all 1024 entries in the table, mapping 4 megabytes
    for (unsigned int i = 0; i < PAGE_TAB_SIZE; i++) {
        // As the address is page aligned, it will always leave 12 bits zeroed (used by attributes).
        // attributes: supervisor level, read/write, present
        first_page_table[i] = (i * 0x1000) | 3;
    }
}