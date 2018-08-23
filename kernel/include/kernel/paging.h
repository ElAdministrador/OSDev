#ifndef _PAGING_H_
#define _PAGING_H_

#include <stdint.h>

// Page directory flags
#define PAGE_DIR_S(x)       ((x) << 0x6) // Size flag (0: 4 KiB, 1: 4 MiB)
#define PAGE_DIR_G(x)       ((x) << 0x7) // Ignore flag

// Page table flags
#define PAGE_PRESENT(x) ((x))           // Page present in memory
#define PAGE_RW(x)      ((x) << 0x1)    // Read/Write flag
#define PAGE_US(x)      ((x) << 0x2)    // User/Supervisor mode
#define PAGE_WRT(x)     ((x) << 0x3)    // Write through (HW Cachw)
#define PAGE_CDIS(x)    ((x) << 0x4)    // Cache disabled flag
#define PAGE_A(x)       ((x) << 0x5)    // Accessed flag
#define PAGE_D(x)       ((x) << 0x6)    // Dirty flag
#define PAGE_G(x)       ((x) << 0x7)    // Global flag

#define PAGE_DIR_SIZE 1024
#define PAGE_TAB_SIZE 1024

uint32_t page_directory[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
uint32_t first_page_table[PAGE_TAB_SIZE] __attribute__((aligned(4096)));

/*
 * Initialize blank page directory.
 * Used first when there aren't any page tables yet.
 */
void blank_page_dir(uint32_t*);

/*
 * Initialize a blank page table.
 * Entry flags: supervisor, read&write, present
 */
void blank_page_table(uint32_t*);

// Enable the paging.
extern void enablePaging(uint32_t page_directory_addr);

#endif