#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/mem_init.h>
#include <string.h>

void kernel_main(void) {

	// Initialize memory management
	init_gdt();
	init_paging();

	// Initialize terminal and perform some tests.
	terminal_initialize();
	printf("Hello, %s%d%d!\n", "deros v", 0,1);

	printf("\n");
	uint32_t t1 = *((uint32_t*) 0x100000);
	uint32_t t2 = *((uint32_t*) 0x101000);
	printf("t1 %p\n", &t1);
	printf("t2 %p\n", &t2);
	printf("tp1 0x%x\n", t1);
	printf("tp2 0x%x\n", t2);

	printf ("\n");
	while(1) {
		char c = getChar();
		if (c != 0) {
			printf("%c", c);
		}
	}
}