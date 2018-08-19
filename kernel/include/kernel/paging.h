#ifndef _PAGING_H_
#define _PAGING_H_

#include <stdint.h>

#define PAGE_DIR_SIZE 1024
#define PAGE_TAB_SIZE 1024

uint32_t page_directory[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
uint32_t first_page_table[PAGE_TAB_SIZE] __attribute__((aligned(4096)));

/*
 * Create a blank page directory.
 * Used first when there aren't any page tables yet.
 */
void blank_page_dir(void);

// TODO real page handler functions
void fill_first_page_table(void);

// Enable the paging.
extern void enablePaging();

#endif