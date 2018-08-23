#ifndef _MEM_INIT_H_
#define _MEM_INIT_H_

#include <kernel/gdt.h>
#include <kernel/paging.h>

#define GDT_SIZE 12

uint64_t GDT[GDT_SIZE];
static const uint32_t GDT_BASE_ADDRESS = (uint32_t) &GDT;
static const uint32_t GDT_LIMIT_ADDRESS = GDT_BASE_ADDRESS + sizeof(GDT);

uint32_t page_directory[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
uint32_t master_page_table[PAGE_TAB_SIZE] __attribute__((aligned(4096)));

/*
 * Wrap up the loading of the GDT and set the default descriptors.
 */
void init_gdt(void);

/*
 * Loading page directory and page tables and activate paging.
 */
void init_paging(void);

#endif