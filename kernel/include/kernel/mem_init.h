#ifndef _MEM_INIT_H_
#define _MEM_INIT_H_

#include <kernel/gdt.h>

#define GDT_SIZE 12

uint64_t GDT[GDT_SIZE];
static const uint32_t GDT_BASE_ADDRESS = (uint32_t) &GDT;
static const uint32_t GDT_LIMIT_ADDRESS = GDT_BASE_ADDRESS + sizeof(GDT);

/*
 * Wrap up the loading of the GDT and set the default descriptors.
 */
void init_gdt(void);

#endif