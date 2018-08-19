#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/keyboard.h>
#include <kernel/mem_init.h>
#include <string.h>

void kernel_main(void) {

	// Initialize terminal and perform some tests.
	terminal_initialize();
	printf("Hello, %s%d%d!\n", "deros v", 0,1);

	init_gdt();

	printf ("\n");
	while(1) {
		char c = getChar();
		if (c != 0) {
			printf("%c", c);
		}
	}
}